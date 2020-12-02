#include "Dot.h"

namespace angelogames {

	Dot::Dot(SDL_Renderer* renderer) {

        log = std::make_unique <Logging>("dot.log");

        m_dot_texture = nullptr;

        //Initialize the offsets
        m_pos_x = 0;
        m_pos_y = 0;
        //Initialize the velocity
        m_vel_x = 0;
        m_vel_y = 0;
        //Initialise the position
        m_width = 0;
        m_height = 0;

        LoadTextures(renderer);

	}

	Dot::~Dot() 
    {

        log->close();
	}

    void Dot::Close()
    {
        if (m_dot_texture != nullptr)
        {
            SDL_DestroyTexture(m_dot_texture);
            m_dot_texture = nullptr;
            m_width = 0;
            m_height = 0;
        }
    }

    void Dot::LoadTextures(SDL_Renderer* renderer) 
    {
        // path to png file
        static const std::string dot_path = "img/dot.png";

        //Load image at specified path
        SDL_Surface* loaded_surface = IMG_Load(dot_path.c_str());

        if (loaded_surface == nullptr)
            log->write("LoadTextures: Error loading surface");
        else {
            //Create texture from surface pixels
            m_dot_texture = SDL_CreateTextureFromSurface(renderer, loaded_surface);

            if (m_dot_texture == nullptr)
                log->write("LoadTextures: Error loading texture");
            else
            {
                //Get image dimensions
                m_width = loaded_surface->w;
                m_height = loaded_surface->h;
            }            
        }
        loaded_surface = nullptr;
        SDL_FreeSurface(loaded_surface);

        std::string msg = "LoadTextures: Successfully loaded texture " + dot_path;
        log->write(msg);       

    }

    void Dot::EventHandler(SDL_Event& e)
    {
        //If a key was pressed
        if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
        {
            //Adjust the velocity
            switch (e.key.keysym.sym)
            {
            case SDLK_UP: m_vel_y -= m_kVelocity; break;
            case SDLK_DOWN: m_vel_y += m_kVelocity; break;
            case SDLK_LEFT: m_vel_x -= m_kVelocity; break;
            case SDLK_RIGHT: m_vel_x += m_kVelocity; break;
            }
        }
        //If a key was released
        else if (e.type == SDL_KEYUP && e.key.repeat == 0)
        {
            //Adjust the velocity
            switch (e.key.keysym.sym)
            {
            case SDLK_UP: m_vel_y += m_kVelocity; break;
            case SDLK_DOWN: m_vel_y -= m_kVelocity; break;
            case SDLK_LEFT: m_vel_x += m_kVelocity; break;
            case SDLK_RIGHT: m_vel_x -= m_kVelocity; break;
            }
        }
    }
    void Dot::Move(int screen_width, int screen_height)
    {
        //Move the dot left or right
        m_pos_x += m_vel_x;

        //If the dot went too far to the left or right
        if ((m_pos_x < 0) || (m_pos_x + m_width > screen_width))
        {
            //Move back
            m_pos_x -= m_vel_x;
        }

        //Move the dot up or down
        m_pos_y += m_vel_y;

        //If the dot went too far up or down
        if ((m_pos_y < 0) || (m_pos_y + m_height > screen_height))
        {
            //Move back
            m_pos_y -= m_vel_y;
        }
    }

    void Dot::Render(SDL_Renderer* renderer, SDL_Rect* clip, double angle, SDL_Point* center)
    {
        //Set rendering space and render to screen
        SDL_Rect render_quad = { m_pos_x, m_pos_y, m_width, m_height };

        //Set clip rendering dimensions
        if (clip != NULL)
        {
            render_quad.w = clip->w;
            render_quad.h = clip->h;
        }

        //Render to screen
        SDL_RenderCopyEx(renderer, m_dot_texture, clip, &render_quad, angle, center, SDL_FLIP_NONE);

    }
}
