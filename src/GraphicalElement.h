class GraphicalElement {

	public:
		GraphicalElement(float width, float height, SDL_Texture *image);
		float getWidth();
		float getHeight();
		SDL_Texture* getSprite();
		virtual void render(SDL_Renderer *renderer) = 0;
		virtual void update() = 0;

	private:
		float width;
		float height;
		SDL_Texture* sprite;
};