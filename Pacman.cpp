#include "Pacman.h"

namespace angelogames {

    Pacman::Pacman(SDL_Renderer* renderer) {

        //Initialises the log file
        log = std::make_unique <Logging>("pacman.log");
        //Initialises the pacman texture with nullptr
        m_pacman = nullptr;
        //Initialize the offsets
        m_pos_x = 100;
        m_pos_y = 100;
        //Initialize the velocity
        m_vel_x = 0;
        m_vel_y = 0;
        //Initialise the direction
        m_direction = (int)m_eAnimation::WalkRight;

        //Load the pacman texture and sprite clips
        LoadTextures(renderer);

    }

    Pacman::~Pacman()
    {
        //Resets sprite clip positons
        /*
        for (auto& i : m_animation_clips) {
            std::get<0>(i) = 0;
            std::get<1>(i) = 0;
            std::get<2>(i) = 0;
            std::get<3>(i) = 0;
            std::get<4>(i) = 0;
            std::get<5>(i) = 0;
            std::get<6>(i) = 0;
            std::get<7>(i) = 0;
        }*/

        //Free texture memory
        if (m_pacman != nullptr)
        {
            //SDL_DestroyTexture(m_pacman);
            m_pacman = nullptr;
        }

        //Close log
        log->close();
    }


    void Pacman::LoadTextures(SDL_Renderer* renderer)
    {
        // path to png file
        static const std::string dot_path = "assets/sprites/pacman.png";

        //Load image at specified path
        SDL_Surface* loaded_surface = IMG_Load(dot_path.c_str());

        if (loaded_surface == nullptr)
            log->write("LoadTextures: Error loading surface");
        else {
            //Create texture from surface pixels
            m_pacman = SDL_CreateTextureFromSurface(renderer, loaded_surface);

            if (m_pacman == nullptr)
                log->write("LoadTextures: Error loading pacman texture");
            else
            {
                std::string msg = "LoadTextures: Successfully loaded texture " + dot_path;
                log->write(msg);

                for (int i = 0; i < m_AnimationFrames; i++) 
                {
                    m_animation_clips[(int)m_eAnimation::WalkRight][i].x = i * m_pacman_width;
                    m_animation_clips[(int)m_eAnimation::WalkRight][i].y = 0;
                    m_animation_clips[(int)m_eAnimation::WalkRight][i].w = m_pacman_width;
                    m_animation_clips[(int)m_eAnimation::WalkRight][i].h = m_pacman_height;
                }
                for (int i = 0; i < m_AnimationFrames; i++)
                {
                    m_animation_clips[(int)m_eAnimation::WalkLeft][i].x = i * m_pacman_width;
                    m_animation_clips[(int)m_eAnimation::WalkLeft][i].y = m_pacman_height;
                    m_animation_clips[(int)m_eAnimation::WalkLeft][i].w = m_pacman_width;
                    m_animation_clips[(int)m_eAnimation::WalkLeft][i].h = m_pacman_height;
                }
                for (int i = 0; i < m_AnimationFrames; i++)
                {
                    m_animation_clips[(int)m_eAnimation::WalkUp][i].x = i * m_pacman_width;
                    m_animation_clips[(int)m_eAnimation::WalkUp][i].y = m_pacman_height * 2;
                    m_animation_clips[(int)m_eAnimation::WalkUp][i].w = m_pacman_width;
                    m_animation_clips[(int)m_eAnimation::WalkUp][i].h = m_pacman_height;
                }
                for (int i = 0; i < m_AnimationFrames; i++)
                {
                    m_animation_clips[(int)m_eAnimation::WalkDown][i].x = i * m_pacman_width;
                    m_animation_clips[(int)m_eAnimation::WalkDown][i].y = m_pacman_height * 3;
                    m_animation_clips[(int)m_eAnimation::WalkDown][i].w = m_pacman_width;
                    m_animation_clips[(int)m_eAnimation::WalkDown][i].h = m_pacman_height;
                }

                m_beginning_clip.x = 32;
                m_beginning_clip.y = 0;
                m_beginning_clip.w = m_pacman_width;
                m_beginning_clip.h = m_pacman_height;

                log->write("LoadTextures: Successfully loaded sprite clips");

            }
        }

        loaded_surface = nullptr;
        SDL_FreeSurface(loaded_surface);

    }

    void Pacman::EventHandler(SDL_Event& e)
    {
        //If a key was pressed
        if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
        {
            //Adjust the velocity
            switch (e.key.keysym.sym)
            {
            case SDLK_UP: m_vel_y -= m_kVelocity; m_direction = (int)m_eAnimation::WalkUp; break;
            case SDLK_DOWN: m_vel_y += m_kVelocity; m_direction = (int)m_eAnimation::WalkDown; break;
            case SDLK_LEFT: m_vel_x -= m_kVelocity; m_direction = (int)m_eAnimation::WalkLeft;  break;
            case SDLK_RIGHT: m_vel_x += m_kVelocity; m_direction = (int)m_eAnimation::WalkRight; break;
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
    void Pacman::Move(int screen_width, int screen_height)
    {
        //Move the pacman left or right
        m_pos_x += m_vel_x;

        //If the pacman went too far to the left or right
        if ((m_pos_x < 0) || (m_pos_x + m_pacman_width > screen_width))
        {
            //Move back
            m_pos_x -= m_vel_x;
        }

        //Move the pacman up or down
        m_pos_y += m_vel_y;

        //If the pacman went too far up or down
        if ((m_pos_y < 0) || (m_pos_y + m_pacman_height > screen_height))
        {
            //Move back
            m_pos_y -= m_vel_y;
        }
    }

    void Pacman::Render(SDL_Renderer* renderer, int frame, int screen_width, int screen_height, SDL_Rect* clip, double angle, SDL_Point* center)
    {

        //Set rendering space
        SDL_Rect currentClip = m_animation_clips[m_direction][frame];
        //SDL_Rect render_quad = { (screen_width-currentClip.x)/2, (screen_height - currentClip.y) / 2, m_animation_clips[(int)m_eAnimation::WalkRight][frame].w, m_animation_clips[(int)m_eAnimation::WalkRight][frame].h};
        SDL_Rect render_quad = { m_pos_x, m_pos_y, m_animation_clips[(int)m_eAnimation::WalkRight][frame].w, m_animation_clips[(int)m_eAnimation::WalkRight][frame].h };

        //Set clip rendering dimensions
        if (clip != NULL)
        {
            render_quad.w = clip->w;
            render_quad.h = clip->h;
        }

        //Render to screen
        SDL_RenderCopyEx(renderer, m_pacman, &currentClip, &render_quad, angle, center, SDL_FLIP_NONE);

    }

}
