#include "Game.h"
#include "iostream"
#include "TextureManager.h"
#include "Keyboard.h"
#include "TickRate.h"
#include "CollisionManager.h"
#include "Enemy.h"
#include "Upgrade.h"
#include "SDL_ttf.h"
#include "SpriteAnimation.h"
#include "Config.h"
#include "LevelUpMenu.h"
#include "AxeProjectile.h"
#include "Timer.h"
#include <time.h>
#include "GUIRenderer.h"
#include "EnemySpawner.h"
#include "AudioManager.h"
#include <SDL2/SDL.h>
#include "GameStateManager.h"

using namespace Config;

const char *pathFont = "assets/fonts/dogica.ttf";
int windowWidth, windowHeight;

bool Game::debugMode = true;

std::unique_ptr<Player> player;
std::unique_ptr<Enemy> enemy;
std::vector<std::unique_ptr<Enemy>> enemies;
std::vector<GraphicalElement *> allElements;
std::unique_ptr<CollisionManager> collision;
std::unique_ptr<Keyboard> keyboard;
std::unique_ptr<TickRate> tickRate;
std::unique_ptr<SpriteAnimation> playerAnimation;
std::unique_ptr<LevelUpMenu> levelUpMenu;
std::vector<std::unique_ptr<Projectile>> projectiles;
std::vector<std::unique_ptr<SpriteAnimation>> ownedAnimations;
std::unique_ptr<EnemySpawner> enemySpawner;

std::string lastFpsText;
std::string lastTimeText;
std::string lastXpText;
SDL_Texture *fpsTexture = nullptr;
SDL_Texture *timeTexture = nullptr;
SDL_Texture *xpTexture = nullptr;
SDL_DisplayMode displayMode;

Game::Game() : timerEvents(2.0f), gameTime(1.0f) {};
Game::~Game() {};

int Game::width = 800; 
int Game::height = 600;

void Game::init(const char *title, int xPos, int yPos, int width, int height, bool fullscreen)
{

	keyboard = std::make_unique<Keyboard>();
	tickRate = std::make_unique<TickRate>();
	collision = std::make_unique<CollisionManager>();
	tileManager = std::make_unique<TileManager>();
	playerAnimation = std::make_unique<SpriteAnimation>();
	levelUpMenu = std::make_unique<LevelUpMenu>();
	int flags = 0;

	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		if (TTF_Init() == -1)
		{
			setIsRunning(false);
			return;
		}

		if (!AudioManager::getInstance().init())
		{
			setIsRunning(false);
			return;
		}

		window = SDL_CreateWindow(title, xPos, yPos, width, height, flags);
		SDL_GetWindowSize(window, &windowWidth, &windowHeight);


		renderer = SDL_CreateRenderer(window, -1, 0);

		AudioManager &audio = AudioManager::getInstance();
		audio.init();
		// Sound Effects
		audio.loadSound("playerHit", "assets/Audios/effects/playerDamage.ogg");
		audio.loadSound("gameOver", "assets/Audios/effects/gameOver.mp3");
		audio.loadSound("AxeThrow", "assets/Audios/effects/AxeThrow.mp3");
		// Musics
		audio.loadMusic("backgroundMusic", "assets/Audios/Music/testTheme.ogg");
		audio.playMusic("backgroundMusic");

		TextureManager::init(renderer);
		loadResources();
		enemySpawner = std::make_unique<EnemySpawner>(Config::MAX_ENEMIES, Config::SPAWN_INTERVAL, windowWidth, windowHeight);
		enemySpawner->loadAllEnemiesFromFolder("assets/data/enemies");
		levelUpMenu->init("assets/data/upgrades.json");

		tileManager->loadMap("assets/map/tileset.json", "assets/data/tiles.json", renderer);

		initializeEntities();

		setIsRunning(true);
		GameStateManager::getInstance().setState(GameState::InGame);
	}
	else
	{
		setIsRunning(false);
		GameStateManager::getInstance().setState(GameState::InLose);
	}
}

void Game::events()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
		{
			GameStateManager::getInstance().setState(GameState::InLose);
		}
	}
}

void Game::clean()
{

	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	TextureManager::cleanTexture();

	SDL_DestroyTexture(fpsTexture);
	SDL_DestroyTexture(timeTexture);
	SDL_DestroyTexture(xpTexture);

	AudioManager::getInstance().clean();

	TTF_Quit();
	SDL_Quit();

	std::cout << "Jogo limpo" << std::endl;
}

void Game::render()
{

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
	SDL_RenderClear(renderer);

	tileManager->renderMap(renderer, player->getCollider());

	SDL_GetWindowSize(window, &windowWidth, &windowHeight);

	if (player != nullptr)
	{
		player->render(renderer);
	}
	else
	{
		std::cout << "Player não está inicializado!" << std::endl;
	}

	for (auto &e : enemies)
	{
		e->render(renderer);
	}

	if (fpsTexture == nullptr)
	{
		std::cerr << "Falha ao criar textura de FPS!" << std::endl;
	}

	if (fpsTexture != nullptr)
	{
		int textW = 0, textH = 0;
		SDL_QueryTexture(fpsTexture, nullptr, nullptr, &textW, &textH);
		SDL_Rect fpsRect = {10, 10, textW, textH};
		SDL_RenderCopy(renderer, fpsTexture, nullptr, &fpsRect);
	}

	if (timeTexture != nullptr)
	{
		int textW = 0, textH = 0;
		SDL_QueryTexture(timeTexture, nullptr, nullptr, &textW, &textH);
		SDL_Rect timeRect = {(windowWidth - textW) / 2, 10, textW, textH};
		SDL_RenderCopy(renderer, timeTexture, nullptr, &timeRect);
	}

	if (xpTexture != nullptr)
	{
		int textW = 0, textH = 0;
		SDL_QueryTexture(xpTexture, nullptr, nullptr, &textW, &textH);
		SDL_Rect xpRect = {10, 25, textW, textH};
		SDL_RenderCopy(renderer, xpTexture, nullptr, &xpRect);
	}

	GUIRenderer::renderPlayerHpBar(renderer, player.get());
	GUIRenderer::renderXpBar(renderer, player.get());
	GUIRenderer::renderItems(renderer, player.get());
	GUIRenderer::renderPlayerInfo(renderer, player.get());

	for (auto &proj : projectiles)
	{
		proj->render(renderer);
	}
	/*
	if(getDebugMode()){
		collision->debugDrawColliders(renderer, allElements, camera->getOffSet());
	}
	*/
	SDL_RenderPresent(renderer);
}

void Game::update()
{
	if (GameStateManager::getInstance().isInLose())
	{
		setIsRunning(false);
		return;
	}

	if (!GameStateManager::getInstance().isInGame())
		return;

	tickRate->update();
	float dt = tickRate->getDeltaTime();

	timerEvents.update(dt);
	gameTime.update(dt);

	if (player->getLevel() > levelUpMenu->lastUpgradedLevel)
	{
		GameStateManager::getInstance().setState(GameState::InUpgrade);
		TTF_Font *font = TTF_OpenFont(pathFont, 10);
		levelUpMenu->show(renderer, font, *player, windowWidth, windowHeight);
		TTF_CloseFont(font);
		levelUpMenu->lastUpgradedLevel++;
		tickRate->reset();
		GameStateManager::getInstance().setState(GameState::InGame);
	}

	if (GameStateManager::getInstance().isInGame())
	{
		if (timerEvents.hasElapsed())
		{
			shootProjectile();
			timerEvents.reset();
		}

		player->update(dt);
		keyboard->update(*player, dt);
		CameraManager::getCameraManager()->follow(player->getPosition());
		keyboard->update(*player, dt);
	}
	collision->handleCollisionMap(player.get(), *tileManager, tileManager->getMapWidth(), tileManager->getMapHeight());

	// if (!allElements.empty()) {
	//     CollisionManager::handleCollisions(allElements);
	// } else {
	//     std::cerr << "allElements vazio para gerenciar a colisão" << std::endl;
	// }
	if (!enemies.empty())
	{
		CollisionManager::handlePlayerCollisions(player.get(), enemies);
	}
	if (!enemies.empty() && !projectiles.empty())
	{
		CollisionManager::handleProjectileCollisions(player.get(), enemies, projectiles);
	}

		enemySpawner->update(gameTime.getElapsedTime(), player.get(), enemies);

		for (auto &e : enemies)
		{
			Vector toPlayer = player->getPosition() - e->getPosition();
			toPlayer.normalize();
			e->setSpeed(toPlayer * e->getMovSpeed());
			e->update(dt);
		}

		for (auto &proj : projectiles)
			proj->update(dt);

		if (!enemies.empty())
			CollisionManager::handlePlayerCollisions(player.get(), enemies);

		if (!enemies.empty() && !projectiles.empty())
			CollisionManager::handleProjectileCollisions(player.get(), enemies, projectiles);
	}

	removeDeadEntities();
	updateFpsDisplay();
	updateClockDisplay();
	updateXp();
}

void Game::loadResources()
{

	// player
	TextureManager::loadTexture("assets/sprites/classes/spriteSheets/warrior/idle/idle-left.png", "warrior-idle-left");
	TextureManager::loadTexture("assets/sprites/classes/spriteSheets/warrior/idle/idle-right.png", "warrior-idle-right");
	TextureManager::loadTexture("assets/sprites/classes/spriteSheets/warrior/walk/walk-left.png", "warrior-walk-left");
	TextureManager::loadTexture("assets/sprites/classes/spriteSheets/warrior/walk/walk-right.png", "warrior-walk-right");
	TextureManager::loadTexture("assets/sprites/classes/spriteSheets/warrior/death/guerreiro-death.png", "death-player");
	TextureManager::loadTexture("assets/sprites/classes/spriteSheets/warrior/hurt/guerreiro-hurt.png", "player-taken-damage");

	// enemies
	TextureManager::loadTexture("assets/sprites/enemies/slime.png", "slime");
	TextureManager::loadTexture("assets/sprites/enemies/esqueleto.png", "skeleton");
	TextureManager::loadTexture("assets/sprites/enemies/morcego.png", "morcego");
	TextureManager::loadTexture("assets/sprites/enemies/olho.png", "olho");
	TextureManager::loadTexture("assets/sprites/enemies/zombie.png", "zombie");

	// tiles
	TextureManager::loadTexture("assets/sprites/tiles/flor.png", "flor");
	TextureManager::loadTexture("assets/sprites/tiles/florDois.png", "florDois");
	TextureManager::loadTexture("assets/sprites/tiles/grama.png", "grama");
	TextureManager::loadTexture("assets/sprites/tiles/gramaTipoDois.png", "gramaTipoDois");
	TextureManager::loadTexture("assets/sprites/tiles/gramaTipoTres.png", "gramaTipoTres");
	TextureManager::loadTexture("assets/sprites/tiles/lama.png", "lama");
	TextureManager::loadTexture("assets/sprites/tiles/pedra.png", "pedra");
	TextureManager::loadTexture("assets/sprites/tiles/grama.png", "simpleTile");
	// GUI
	TextureManager::loadTexture("assets/sprites/gui/upgradeMenu.png", "upgradeMenu");
	TextureManager::loadTexture("assets/sprites/gui/xpBar.png", "xpBar");
	TextureManager::loadTexture("assets/sprites/gui/infoJogador.png", "infoJogador");

	// Upgrades
	TextureManager::loadTexture("assets/sprites/upgrades/PowerStrike.png", "PowerStrike");
	TextureManager::loadTexture("assets/sprites/upgrades/TitanBlessing.png", "TitanBlessing");
	TextureManager::loadTexture("assets/sprites/upgrades/HealthSurge.png", "HealthSurge");

	// projectiles
	TextureManager::loadTexture("assets/sprites/effects/axe-spritesheet.png", "axe");
}

void Game::limitFPS(float targetFPS)
{
	static Uint64 previousTicks = SDL_GetPerformanceCounter();
	Uint64 currentTicks = SDL_GetPerformanceCounter();

	float frameDelay = 1000.0f / targetFPS;

	float elapsedTime = (currentTicks - previousTicks) / (float)SDL_GetPerformanceFrequency() * 1000.0f;

	if (elapsedTime < frameDelay)
	{
		SDL_Delay(static_cast<Uint32>(frameDelay - elapsedTime));
	}

	previousTicks = SDL_GetPerformanceCounter();
}

void Game::initializeEntities()
{

	playerAnimation->addAnimation("walk-right", "warrior-walk-right", 0, 0, 32, 32, 4, true);
	playerAnimation->addAnimation("walk-left", "warrior-walk-left", 0, 0, 32, 32, 4, true);
	playerAnimation->addAnimation("idle-right", "warrior-idle-right", 0, 0, 34, 32, 6, true);
	playerAnimation->addAnimation("idle-left", "warrior-idle-left", 0, 0, 34, 32, 6, true);

	playerAnimation->addAnimation("death-player", "death-player", 0, 0, 32, 32, 6, false);
	playerAnimation->addAnimation("player-taken-damage", "player-taken-damage", 0, 0, 32, 32, 3, false);

	playerAnimation->play("idle-right");

	int mapCenterX = tileManager->getMapWidthInPixels() / 2;
	int mapCenterY = tileManager->getMapHeightInPixels() / 2;
	Vector centerPos(mapCenterX, mapCenterY);
	Vector zero(0, 0);

	player = std::make_unique<Player>(
		Config::PLAYER_SIZE,
		playerAnimation.get(),
		centerPos,
		Config::PLAYER_SPEED,
		Config::PLAYER_HP,
		Config::PLAYER_HP,
		Config::PLAYER_ATTACK_RATE,
		Config::PLAYER_MOV_SPEED,
		Config::PLAYER_INITIAL_XP,
		Config::PLAYER_INITIAL_LEVEL,
		Config::INITIAL_NEXT_LEVEL_EXPERIENCE,
		Config::PLAYER_ATTACK_SPEED,
		Config::PLAYER_IS_MOVING,
		Config::PLAYER_INITIAL_DIRECTION,
		Config::PLAYER_DAMAGE_COOLDOWN,
		Config::PLAYER_INVULNERABILITY_TIME);

	player->setAnimations(playerAnimation.get());
	allElements.push_back(player.get());
}

void Game::updateFpsDisplay()
{
	int textW, textH;
	std::string currentFpsText = std::to_string(tickRate->getFPS());

	std::string fullText = "FPS: " + currentFpsText;

	SDL_Color black = {0, 0, 0, 255};

	if (currentFpsText != lastFpsText)
	{
		lastFpsText = currentFpsText;

		if (fpsTexture != nullptr)
			SDL_DestroyTexture(fpsTexture);

		TTF_Font *font = TTF_OpenFont(pathFont, 10);
		if (!font)
		{
			std::cerr << TTF_GetError() << std::endl;
			return;
		}

		textW = 0, textH = 0;
		if (TTF_SizeText(font, fullText.c_str(), &textW, &textH) != 0)
		{
			std::cerr << TTF_GetError() << std::endl;
			TTF_CloseFont(font);
			return;
		}

		fpsTexture = TextureManager::renderText(fullText, pathFont, black, 10);
		TTF_CloseFont(font);
	}
}

void Game::updateClockDisplay()
{
	std::string timeText = gameTime.clock();

	SDL_Color black = {0, 0, 0, 255};

	if (timeText != lastTimeText)
	{
		lastTimeText = timeText;

		if (timeTexture != nullptr)
		{
			SDL_DestroyTexture(timeTexture);
			timeTexture = nullptr;
		}

		TTF_Font *font = TTF_OpenFont(pathFont, 12);
		if (!font)
		{
			std::cerr << "erro: " << TTF_GetError() << std::endl;
			return;
		}

		int textW = 0, textH = 0;

		if (TTF_SizeText(font, timeText.c_str(), &textW, &textH) != 0)
		{
			std::cerr << TTF_GetError() << std::endl;
			TTF_CloseFont(font);
			return;
		}
		timeTexture = TextureManager::renderText(timeText, pathFont, black, 12);
		if (timeTexture == nullptr)
		{
			std::cerr << "Erro ao criar a textura de tempo: " << TTF_GetError() << std::endl;
		}
		TTF_CloseFont(font);
	}
}

void Game::updateXp()
{
	std::string xpText = "LEVEL: " + std::to_string(player->getLevel()) + " XP:" + std::to_string(static_cast<int>(player->getXp())) + " / " + std::to_string(static_cast<int>(player->getXpNextLevel()));
	if (xpText != lastXpText)
	{
		SDL_Color black = {0, 0, 0, 255};
		lastXpText = xpText;

		if (xpTexture != nullptr)
		{
			SDL_DestroyTexture(xpTexture);
			xpTexture = nullptr;
		}

		TTF_Font *font = TTF_OpenFont(pathFont, 12);
		if (!font)
		{
			std::cerr << "erro: " << TTF_GetError() << std::endl;
			return;
		}

		int textW = 0, textH = 0;

		if (TTF_SizeText(font, xpText.c_str(), &textW, &textH) != 0)
		{
			std::cerr << TTF_GetError() << std::endl;
			TTF_CloseFont(font);
			return;
		}
		xpTexture = TextureManager::renderText(xpText, pathFont, black, 12);
		if (xpTexture == nullptr)
		{
			std::cerr << "Erro ao criar a textura de tempo: " << TTF_GetError() << std::endl;
		}
		TTF_CloseFont(font);
	}
}

void Game::shootProjectile()
{
	if (enemies.empty())
		return;

	Vector playerPos = player->getPosition();

	Enemy *target = nullptr;
	float closestDistanceSq = std::numeric_limits<float>::max();

	for (const auto &e : enemies)
	{
		float distSq = (e->getPosition() - playerPos).length_squared();
		if (distSq < closestDistanceSq)
		{
			closestDistanceSq = distSq;
			target = e.get();
		}
	}

	if (!target)
		return;

	Vector enemyPos = target->getPosition();
	Vector direction = enemyPos - playerPos;
	direction.normalize();

	// Vector spawnOffSet = direction * 10.0f;

	auto anim = std::make_unique<SpriteAnimation>();
	anim->addAnimation("axe-idle", "axe", 0, 0, 32, 32, 1, false);
	anim->addAnimation("axe-right", "axe", 0, 0, 32, 32, 5, true);
	anim->addAnimation("axe-left", "axe", 160, 0, 32, 32, 5, true);
	anim->play("axe-right");

	auto p = std::make_unique<AxeProjectile>(
		playerPos + 10.0f,
		direction,
		150.0f,
		10.0f,
		std::move(anim),
		player.get());

	projectiles.push_back(std::move(p));
	allElements.push_back(projectiles.back().get());
}

void Game::removeDeadEntities()
{
	projectiles.erase(
		std::remove_if(projectiles.begin(), projectiles.end(),
					   [](const std::unique_ptr<Projectile> &p)
					   {
						   return !p->isAlive();
					   }),
		projectiles.end());

	enemies.erase(
		std::remove_if(enemies.begin(), enemies.end(),
					   [](const std::unique_ptr<Enemy> &e)
					   {
						   return !e->isAlive();
					   }),
		enemies.end());

	allElements.clear();
	allElements.push_back(player.get());
	for (auto &e : enemies)
		allElements.push_back(e.get());
	for (auto &p : projectiles)
		allElements.push_back(p.get());
}
