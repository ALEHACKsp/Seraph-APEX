/*                                       *
 * fgui - an extensive oop gui framework *
 *                                       */

// includes
#include "notifications.hh"
#include "../handler/handler.hh"

fgui::notification::notification() {

    fgui::notification::m_x = 0;
    fgui::notification::m_y = 50;
    fgui::notification::m_width = 150;
    fgui::notification::m_height = 45;
    fgui::notification::m_stay_time = 100;
}

//---------------------------------------------------------
void fgui::notification::draw() {

    // get the window style
	auto style = handler::get_style();

	// screen size
	int screen_width, screen_height;
	fgui::render.get_screen_size(screen_width, screen_height);

    if (m_info.empty())
        return;

	for (std::size_t i = 0; i < m_info.size(); i++) {

		// notification text size
		fgui::dimension text_size = fgui::render.get_text_size(fgui::notification::get_font(), m_info[i].text);

		// notification area
		fgui::rect area = { 0, 0, 0, 0 };

        if (m_info[i].animation_type ==  fgui::animation_type::LINEAR) {
            
            area = { m_x + (screen_width - m_info[i].animation_progress), m_y + (m_height * static_cast<int>(i)), m_width + 30, m_height };
            
            // notification body
		    fgui::render.outline(area.left, area.top, area.right, area.bottom, fgui::color(style.notifications.at(0), 235));
		    fgui::render.rect(area.left + 1 , area.top + 1, 1, area.bottom - 2, fgui::color(style.notifications.at(3)));
		    fgui::render.rect(area.left + 2, area.top + 2, area.right - 4, area.bottom - 4, fgui::color(style.notifications.at(1), 235));

			// notification text
            if (m_info[i].text.length() > 32)
			    fgui::render.text(area.left + 10, area.top + (area.bottom / 2) - (text_size.height / 2), fgui::color(style.text.at(0), 235), fgui::notification::get_font(), m_info[i].text.replace(m_info[i].text.begin() + 32, m_info[i].text.end(), "..."));
            else
			    fgui::render.text(area.left + 10, area.top + (area.bottom / 2) - (text_size.height / 2), fgui::color(style.text.at(0), 235), fgui::notification::get_font(), m_info[i].text);
        }

        else if (m_info[i].animation_type == fgui::animation_type::FADE) {
            
            area = { m_x + (screen_width - m_width), m_y + (m_height * static_cast<int>(i)), m_width + 30, m_height };

		    // notification body
		    fgui::render.outline(area.left, area.top, area.right, area.bottom, fgui::color(style.notifications.at(0), m_info[i].animation_progress));
		    fgui::render.rect(area.left + 1 , area.top + 1, 1, area.bottom - 2, fgui::color(style.notifications.at(3), m_info[i].animation_progress));
		    fgui::render.rect(area.left + 2, area.top + 2, area.right - 4, area.bottom - 4, fgui::color(style.notifications.at(1), m_info[i].animation_progress));

			// notification text
            if (m_info[i].text.length() > 32)
			    fgui::render.text(area.left + 10, area.top + (area.bottom / 2) - (text_size.height / 2), fgui::color(style.text.at(0), m_info[i].animation_progress), fgui::notification::get_font(), m_info[i].text.replace(m_info[i].text.begin() + 32, m_info[i].text.end(), "..."));
            else
			    fgui::render.text(area.left + 10, area.top + (area.bottom / 2) - (text_size.height / 2), fgui::color(style.text.at(0), m_info[i].animation_progress), fgui::notification::get_font(), m_info[i].text);
        }
    }
}

//---------------------------------------------------------
void fgui::notification::update() {

    static const int increase_value = 1;
    static const int alpha_value = 200;

    if (m_info.empty())
        return;

    for (std::size_t i = 0; i < m_info.size(); i++) {

        if (!m_info[i].state) {
            m_info[i].tick = 0;
            m_info[i].text.clear();

            m_info.erase(m_info.begin() + i);
            m_info.shrink_to_fit();
        }

        else if (m_info[i].state) {

            m_info[i].tick += increase_value;

            // linear animation
            if (m_info[i].animation_type == fgui::animation_type::LINEAR) {
                
                if (m_info[i].tick < m_width)
                    m_info[i].animation_progress++;

                // close the notification if it exceeds its time
                if (m_info[i].tick >= m_width + m_stay_time) {

                    m_info[i].animation_progress--;

                if (m_info[i].animation_progress == 0)
                    m_info[i].state = false;
                }
            }

            // fade animation
            else if (m_info[i].animation_type == fgui::animation_type::FADE) {

                if (m_info[i].tick < alpha_value)
                    m_info[i].animation_progress++;
                
                // close the notification if it exceeds its time
                if (m_info[i].tick >= alpha_value + m_stay_time) {

                    m_info[i].animation_progress--;

                    if (m_info[i].animation_progress == 0)
                        m_info[i].state = false;
                }
            }
        }
    }
}

//---------------------------------------------------------
void fgui::notification::handle_input() {

    // screen size
	int screen_width, screen_height;
	fgui::render.get_screen_size(screen_width, screen_height);

    if (m_info.empty())
        return;

    for (std::size_t i = 0; i < m_info.size(); i++) {

		// notification area
		fgui::rect area = { m_x + (screen_width - m_width), m_y + (m_height * static_cast<int>(i)), m_width + 30, m_height };

        // check if the user is hovering the notification area
        if (fgui::input_system::mouse_in_area(area)) {
            
            // close the notification if the user click on it
            if (fgui::input_system::key_held(fgui::external::MOUSE_LEFT))
                m_info[i].state = false;
        }
    }
}