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
#include "Weapon.h"
#include "Attack.h"
#include "Axe.h"
#include "BrassKnuckles.h"
#include "WaveManager.h"
#include "Chakram.h"
#include "Lightning.h"
#include "DamagePopupManager.h"
#include "GameStateManager.h"
#include "SceneManager.h"
#include "scenes/MenuScene.h"
#include "scenes/GameOverScene.h"
#include "TextDisplayManager.h"

using namespace Config;

const char *pathFont = "assets/fonts/dogica.ttf";

bool Game::debugMode = true;

SceneManager& sceneManager = SceneManager::getInstance();

	std::string lastFpsText;
	std::string lastTimeText;
	std::string lastXpText;
	SDL_DisplayMode displayMode;

	Game::Game() : timerEvents(2.0f), gameTime(1.0f) {};
	Game::~Game() {};
	
	void Game::init(SDL_Renderer *render)
	{
		renderer = render;
		keyboard = std::make_unique<Keyboard>();
		tickRate = std::make_unique<TickRate>();
		collision = std::make_unique<CollisionManager>();
		tileManager = std::make_unique<TileManager>();
		playerAnimation = std::make_unique<SpriteAnimation>();
		levelUpMenu = std::make_unique<LevelUpMenu>();
		textDisplay = std::make_unique<TextDisplayManager>(renderer, pathFont);

		if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
		{
			if (!AudioManager::getInstance().init())
			{
				setIsRunning(false);
				return;
			}

			//enemies.clear();
			TextureManager::cleanTexture();

			AudioManager &audio = AudioManager::getInstance();
			audio.init();
			// Sound Effects
			audio.loadSound("playerHit", "assets/Audios/effects/playerDamage.ogg");
			audio.loadSound("gameOver", "assets/Audios/effects/gameover.mp3");
			audio.loadSound("AxeThrow", "assets/Audios/effects/AxeThrow.mp3");
			// Musics
			audio.loadMusic("backgroundMusic", "assets/Audios/Music/testTheme.ogg");
			audio.playMusic("backgroundMusic");
			TextureManager::init(renderer);
			loadResources();
			levelUpMenu->init("assets/data/upgrades.json", "assets/data/weapons.json");

			tileManager->loadMap("assets/map/tileset.json", "assets/data/tiles.json", renderer);
			initializeEntities();

			setIsRunning(true);
			GameStateManager::getInstance().setState(GameState::InGame);
		}
		else
		{
			setIsRunning(false);
			return;
		}

		if (!AudioManager::getInstance().init())
		{
			setIsRunning(false);
			return;
		}


		AudioManager &audio = AudioManager::getInstance();
		audio.init();
		// Sound Effects
		audio.loadSound("playerHit", "assets/Audios/effects/playerDamage.ogg");
		audio.loadSound("gameOver", "assets/Audios/effects/gameover.mp3");
		audio.loadSound("AxeThrow", "assets/Audios/effects/AxeThrow.mp3");
		// Musics
		audio.loadMusic("backgroundMusic", "assets/Audios/Music/testTheme.ogg");
		audio.playMusic("backgroundMusic");

		TextureManager::init(renderer);
		loadResources();

		levelUpMenu->init("assets/data/upgrades.json", "assets/data/weapons.json");

		tileManager->loadMap("assets/map/tileset.json", "assets/data/tiles.json", renderer);
		waveManager = std::make_unique<WaveManager>("assets/data/waves.json", sceneManager.getWidth(), sceneManager.getHeight());
		initializeEntities();

		
		damagePopupManager = std::make_unique<DamagePopupManager>(renderer, "assets/fonts/dogica.ttf", 12, 50);
		collision->setDamagePopupManager(damagePopupManager.get());

		setIsRunning(true);
		GameStateManager::getInstance().setState(GameState::InGame);
}

void Game::render()
{
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
	SDL_RenderClear(renderer);

	tileManager->renderMap(renderer, player->getCollider());

	textDisplay->renderText("fps", 10, 10);
	textDisplay->renderText("clock", 10, 25);
	textDisplay->renderText("xp", 10, 40);

	for (auto &e : enemies)
	{
		e->render(renderer);
	}

	if (player != nullptr)
	{
		player->render(renderer);
	}
	else
	{
		std::cout << "Player não está inicializado!" << std::endl;
	}

	for (auto &weapon : player->getWeapons())
	{
		for (auto &attack : weapon->getAttacks())
		{
			attack->render(renderer);
		}
	}

	damagePopupManager->render(CameraManager::getCameraManager()->getOffSet());

	GUIRenderer::renderPlayerHpBar(renderer, player.get());
	GUIRenderer::renderXpBar(renderer, player.get());
	GUIRenderer::renderItems(renderer, player.get());
	GUIRenderer::renderPlayerInfo(renderer, player.get());
	

	SDL_RenderPresent(renderer);
}

void Game::update(float dt)
{

	if (GameStateManager::getInstance().isInLose())
	{
		setIsRunning(false);
		cleanUp();

		std::cout << "perdeu" << std::endl;
		std::string finalTime = gameTime.clock();
		int level = player->getLevel();
		SceneManager::getInstance().changeScene(new GameOverScene(finalTime, level, enemiesKilled));
		GameStateManager::getInstance().setState(GameState::InMenu);
		return;
	}

	if (!GameStateManager::getInstance().isInGame())
		return;


	timerEvents.update(dt);
	gameTime.update(dt);

	if (player->getLevel() > levelUpMenu->lastUpgradedLevel)
	{
		GameStateManager::getInstance().setState(GameState::InUpgrade);
		TTF_Font *font = TTF_OpenFont(pathFont, 10);
		levelUpMenu->show(renderer, font, *player, sceneManager.getWidth(), sceneManager.getHeight());
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

	damagePopupManager->update(dt);

	if (player->getCurrentHp() <= 0.0f) {
		std::cout << "morreu" << std::endl;
		GameStateManager::getInstance().setState(GameState::InLose);
		std::cout << "morreu inLose" << std::endl;
	}

	if (!enemies.empty())
	{
		collision->handlePlayerCollisions(player.get(), enemies);
		collision->handleProjectileCollisions(player.get(), enemies);
		collision->handleEnemyCollisions(enemies, player.get());
	}


	for (auto &e : enemies)
	{
		Vector toPlayer = player->getPosition() - e->getPosition();
		toPlayer.normalize();
		e->setSpeed(toPlayer * e->getMovSpeed());
		e->update(dt);
	}
	for (auto &weapon : player->getWeapons())
	{
		weapon->update(dt);
	}

	removeDeadEntities();

	if (waveManager)
	{
		waveManager->update(dt, player.get(), enemies);
	}

	updateFpsDisplay();
	updateClockDisplay();
	updateXp();
}

void Game::cleanUp()
{
	TextureManager::cleanTexture();
	textDisplay->clear();

	waveManager->cleanUp();

	AudioManager::getInstance().clean();

	std::cout << "Jogo limpo" << std::endl;
}

void Game::loadResources()
{

	// player
	TextureManager::loadTexture("assets/sprites/classes/spriteSheets/warrior/idle/idle-left.png", "dwarven-idle-left");
	TextureManager::loadTexture("assets/sprites/classes/spriteSheets/warrior/idle/idle-right.png", "dwarven-idle-right");
	TextureManager::loadTexture("assets/sprites/classes/spriteSheets/warrior/walk/walk-left.png", "dwarven-walk-left");
	TextureManager::loadTexture("assets/sprites/classes/spriteSheets/warrior/walk/walk-right.png", "dwarven-walk-right");
	TextureManager::loadTexture("assets/sprites/classes/spriteSheets/warrior/death/dwarven-death.png", "death-player");
	TextureManager::loadTexture("assets/sprites/classes/spriteSheets/warrior/hurt/dwarven-hurt.png", "dwarven-hit");

	// enemies walk
	TextureManager::loadTexture("assets/sprites/enemies/slime.png", "slime");
	TextureManager::loadTexture("assets/sprites/enemies/esqueleto.png", "skeleton");
	TextureManager::loadTexture("assets/sprites/enemies/morcego.png", "morcego");
	TextureManager::loadTexture("assets/sprites/enemies/olho.png", "olho");
	TextureManager::loadTexture("assets/sprites/enemies/zombie.png", "zombie");
	// enemies death
	TextureManager::loadTexture("assets/sprites/enemies/deaths/slime-morte.png", "slime-death");
	TextureManager::loadTexture("assets/sprites/enemies/deaths/esqueleto-morte.png", "skeleton-death");
	TextureManager::loadTexture("assets/sprites/enemies/deaths/morcego-morte.png", "morcego-death");
	TextureManager::loadTexture("assets/sprites/enemies/deaths/olho-morte.png", "olho-death");
	TextureManager::loadTexture("assets/sprites/enemies/deaths/zombie-morte.png", "zombie-death");
	// enemies hit
	TextureManager::loadTexture("assets/sprites/enemies/Hit/slime-hit.png", "slime-hit");
	TextureManager::loadTexture("assets/sprites/enemies/Hit/esqueleto-hit.png", "skeleton-hit");
	TextureManager::loadTexture("assets/sprites/enemies/Hit/morcego-hit.png", "morcego-hit");
	TextureManager::loadTexture("assets/sprites/enemies/Hit/olho-hit.png", "olho-hit");
	TextureManager::loadTexture("assets/sprites/enemies/Hit/zombie-hit.png", "zombie-hit");

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
	TextureManager::loadTexture("assets/sprites/upgrades/AttackBoost.png", "Forca Bruta");
	TextureManager::loadTexture("assets/sprites/upgrades/TitanBlessing.png", "Bencao Titanica");
	TextureManager::loadTexture("assets/sprites/upgrades/HealthSurge.png", "Surto de Saude");
	TextureManager::loadTexture("assets/sprites/upgrades/regen.png", "Regeneracao Vital");
	TextureManager::loadTexture("assets/sprites/upgrades/MovimentSpeed.png", "Aceleracao de Movimento");
	TextureManager::loadTexture("assets/sprites/upgrades/AttackSpeed.png", "Impulso de Ataque");

	// Weapons Icons
	TextureManager::loadTexture("assets/sprites/weapons/icons/fisic/axe.png", "AxeIcon");
	TextureManager::loadTexture("assets/sprites/weapons/icons/fisic/boomerang.png", "BoomerangIcon");
	TextureManager::loadTexture("assets/sprites/weapons/icons/fisic/chakram-icon.png", "ChakramIcon");
	TextureManager::loadTexture("assets/sprites/weapons/icons/fisic/brassknuckles.png", "BrassKnucklesIcon");
	
	TextureManager::loadTexture("assets/sprites/weapons/icons/magic/ifritsFire.png", "IfritFlamesIcon");
	TextureManager::loadTexture("assets/sprites/weapons/icons/magic/lightningJudgment.png", "JudgmentRayIcon");
	TextureManager::loadTexture("assets/sprites/weapons/icons/magic/atoleio.png", "MudPoolIcon");

	// Weapons Effects
	TextureManager::loadTexture("assets/sprites/weapons/animations/axe-spritesheet.png", "axe");
	TextureManager::loadTexture("assets/sprites/weapons/animations/chakram.png", "chakram");
	TextureManager::loadTexture("assets/sprites/weapons/animations/brassknuckles-2.png", "brassKnuckles-attack");
	TextureManager::loadTexture("assets/sprites/weapons/animations/lightning.png", "lightning");
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
	//
	playerAnimation->addAnimation("walk-right", "dwarven-walk-right", 0, 0, 32, 32, 5, true);
	playerAnimation->addAnimation("walk-left", "dwarven-walk-left", 0, 0, 32, 32, 5, true);
	//
	playerAnimation->addAnimation("idle-right", "dwarven-idle-right", 0, 0, 32, 32, 5, true);
	playerAnimation->addAnimation("idle-left", "dwarven-idle-left", 0, 0, 32, 32, 5, true);
	//
	playerAnimation->addAnimation("death-player", "death-player", 0, 0, 32, 32, 5, false);
	playerAnimation->addAnimation("dwarven-hit", "dwarven-hit", 0, 0, 32, 32, 3, false);
	//
	playerAnimation->play("idle-left");

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
		Config::PLAYER_INVULNERABILITY_TIME,
		Config::DAMAGE_MULTIPLIER);
	auto anim = std::make_unique<SpriteAnimation>();
	anim->addAnimation("axe-idle", "axe", 0, 0, 32, 32, 1, false);
	anim->addAnimation("axe-right", "axe", 0, 0, 32, 32, 5, true);
	anim->addAnimation("axe-left", "axe", 160, 0, 32, 32, 5, true);
	anim->play("axe-right");
	std::string desc = "teste";
	std::unique_ptr<Weapon> weapon = std::make_unique<Axe>(
		Config::PLAYER_SIZE,
		anim.get(),
		"Axe");

	auto anim2 = std::make_unique<SpriteAnimation>();
	anim2->addAnimation("idle", "brassKnuckles-attack", 0, 0, 64, 64, 1, false);
	anim2->play("idle");
	std::unique_ptr<Weapon> weapon2 = std::make_unique<BrassKnuckles>(
		Config::PLAYER_SIZE,
		anim2.get(),
		"soco-inglês");

	std::unique_ptr<Weapon> weapon3 = std::make_unique<Chakram>(
		Config::PLAYER_SIZE,
		anim.get(),
		"Chakram");

	std::unique_ptr<Weapon> weapon4 = std::make_unique<Lightning>(
		Config::PLAYER_SIZE,
		anim.get(),
		"Lightning");

	player->getWeapons().push_back(std::move(weapon));
	// player->getWeapons().push_back(std::move(weapon2));
	// player->getWeapons().push_back(std::move(weapon3));
	// player->getWeapons().push_back(std::move(weapon4));
	player->setAnimations(playerAnimation.get());
}

void Game::updateFpsDisplay()
{
	std::string currentFpsText = "FPS: " + std::to_string(sceneManager.getTickRate()->getFPS());
	SDL_Color black = {0, 0, 0, 255};

	textDisplay->updateText("fps", currentFpsText, 10, black);
}

void Game::updateClockDisplay()
{
	std::string timeText = gameTime.clock();
	SDL_Color black = {0, 0, 0, 255};

	textDisplay->updateText("clock", timeText, 12, black);
}

void Game::updateXp()
{
	std::string xpText = "LEVEL: " + std::to_string(player->getLevel()) +
                         " XP: " + std::to_string(static_cast<int>(player->getXp())) +
                         " / " + std::to_string(static_cast<int>(player->getXpNextLevel()));
	SDL_Color black = {0, 0, 0, 255};

	textDisplay->updateText("xp", xpText, 12, black);
}

void Game::shootProjectile()
{
	if (enemies.empty())
		return;

	Vector playerPos = player->getPosition();

	for (const auto &weapon : player->getWeapons())
	{
		if (weapon->getCurrentCooldown() < 0.0f)
		{
			AudioManager &audio = AudioManager::getInstance();
			audio.setEffectsVolume(1.0f);
			audio.playSound("AxeThrow");

			weapon->attack(playerPos, enemies, player.get());
		}
	}
}

void Game::removeDeadEntities()
{

	for (auto &weapon : player->getWeapons())
	{
		auto &attacks = weapon->getAttacks();
		weapon->getAttacks().erase(
			std::remove_if(attacks.begin(), attacks.end(),
						   [](const std::unique_ptr<Attack> &p)
						   {
							   return !p->isAlive();
						   }),
			attacks.end());
	}
	for (auto& e : enemies) {
		if(!e->isAlive() && e->getSpriteAnimation()->animationEnded()) {
			enemiesKilled++;
		}
	}

	enemies.erase(
		std::remove_if(enemies.begin(), enemies.end(),
					   [](const std::unique_ptr<Enemy> &e)
					   {
						   return !e->isAlive() && e->getSpriteAnimation()->animationEnded();
					   }),
		enemies.end());
}


void Game::handleInput(SDL_Event& event) {

}