#include "Screen.h"

namespace angelogames {

	Screen::Screen() 
	{

		log = std::make_unique <Logging>("screen.log");

		//Initialization flag
		bool success = true;

		//Initialize SDL
		if (SDL_Init(SDL_INIT_VIDEO) < 0)
		{
			log->write(SDL_GetError());
			success = false;
		}
		else
		{
			//Set texture filtering to linear
			if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
			{
				log->write("Warning: Linear texture filtering not enabled!");
			}

			//Create window
			m_window = SDL_CreateWindow("Pacman", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, m_kScreenWidth, m_kScreenHeight, SDL_WINDOW_SHOWN);
			
			if (m_window == nullptr)
			{
				log->write(SDL_GetError());
				success = false;
			}
			else {
				//Create renderer for window
				m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
				if (m_renderer == nullptr) {
					log->write(SDL_GetError());
					success = false;
				}
				else
				{

					//SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, 'linear');

					// set logical resolution
					//SDL_RenderSetLogicalSize(renderer, 1024, 768);

					//Initialize renderer color
					SDL_SetRenderDrawColor(m_renderer, 0x00, 0x00, 0x00, 0xFF);
					SDL_RenderClear(m_renderer);

					//Initialize PNG loading
					int image_flags = IMG_INIT_PNG;
					// load support for the JPG and PNG image formats
					int flags = IMG_INIT_JPG | IMG_INIT_PNG;
					int initted = IMG_Init(flags);
					if ((initted & flags) != flags) {
						log->write(IMG_GetError());
						success = false;
					}

					//Initialize SDL_ttf
					if (TTF_Init() == -1)
					{
						log->write(TTF_GetError());
						success = false;
					}


					//Initialize SDL_mixer
					if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
					{
						log->write(Mix_GetError());
						success = false;
					}

					LoadGameTextures();

					//current_texture = nullptr;
					log->write("Init complete.");

				}
			}
		}

		// create one smart pointer to Dot
		m_dot = std::make_unique <Dot>(m_renderer);
		//Create a smart pointer to Pacman
		m_pacman = std::make_unique <Pacman>(m_renderer);
		//Create a smart pointer for the Maze
		m_maze = std::make_unique<Maze>();

		m_frame = 0;

		//std::cout << m_maze->GetTileValue(2, 2) << std::endl;
	}

	Screen::~Screen() 
	{	
		log->write("Killing Screen now.");
		log->close();
	}

	SDL_Texture* Screen::LoadSingleTexture(std::string path) 
	{

		//The final texture
		SDL_Texture* newTexture = nullptr;
		//Load image at specified path
		SDL_Surface* loadedSurface = IMG_Load(path.c_str());

		if (loadedSurface == nullptr)
			log->write("LoadTexture: Error loading surface.");
		else {
			//Create texture from surface pixels
			newTexture = SDL_CreateTextureFromSurface(m_renderer, loadedSurface);

			if (newTexture == nullptr)
				log->write("LoadTexture: Error loading texture.");

		}
		std::string msg = "LoadTexture: Successfully loaded texture " + path;
		log->write(msg);
		loadedSurface = nullptr;
		SDL_FreeSurface(loadedSurface);
		return newTexture;
	}

	void Screen::LoadGameTextures()
	{
		log->write("Loading Textures...");

	}
	void Screen::EventHandler(SDL_Event& event)
	{
		//m_dot->EventHandler(event);
		m_pacman->EventHandler(event);
	}

	void Screen::MoveObjects() 
	{
		//m_dot->Move(m_kScreenWidth, m_kScreenHeight);
		m_pacman->Move(m_kScreenWidth, m_kScreenHeight);
	}


	void Screen::ClearScreen() 
	{
		//reset renderer color
		SDL_SetRenderDrawColor(m_renderer, 0x00, 0x00, 0x00, 0xFF);
		/* Clear the entire screen's back buffer to our selected color. */
		SDL_RenderClear(m_renderer);
	}
	

	void Screen::RenderObjects() 
	{
		ClearScreen();
		//m_dot->Render(m_renderer);

		//Render current frame
		m_pacman->Render(m_renderer, m_frame/m_kAnimationDelayFrames, m_kScreenWidth, m_kScreenHeight);

	}


	void Screen::UpdateScreen()
	{
		// render to screen
		SDL_RenderPresent(m_renderer);

		m_frame++;

		//Cycle animation
		if (m_frame / m_kAnimationDelayFrames >= m_pacman->GetAnimationFrames())
			m_frame = 0; // reset

	}


	void Screen::Close()
	{
		m_dot->Close();

		//Destroy window	
		SDL_DestroyRenderer(m_renderer);
		SDL_DestroyWindow(m_window);
		m_renderer = nullptr;
		m_window = nullptr;

		//Quit SDL subsystems
		IMG_Quit();
		TTF_Quit();
		SDL_Quit();

		
	}
}