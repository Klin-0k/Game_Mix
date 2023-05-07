#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <time.h>

Game1::Game1() {
  std::srand(time(NULL));

  background = new Fon(PATH_TO_RESOURCES"/Game1/images/background*.png",
                       1, 0, parent_, false);
  game_background_image.loadFromFile(PATH_TO_RESOURCES"/Game1/images/game_background.jpg");
  game_over_background_image.loadFromFile(PATH_TO_RESOURCES"/Game1/images/game_over_background.jpg");
  SetUpdateEvent([this] (double dt) {Update(dt); });
  game_background =  new Object(game_background_image, parent_, false);
  game_over_background =  new Object(game_over_background_image, parent_, false);
  indent_x = static_cast<float>(0.02 * parent_->getSize().x);
  indent_y = static_cast<float>(0.02 * parent_->getSize().y);
  game_background->Move(indent_x, indent_y);
  game_background->SetScale(static_cast<float>(0.5 * parent_->getSize().x) / game_background->GetLocalWidth(),
                            static_cast<float>(0.96 * parent_->getSize().y) / game_background->GetLocalHeight());
  game_over_background->Move(indent_x, indent_y);
  game_over_background->SetScale(static_cast<float>(0.5 * parent_->getSize().x) / game_over_background->GetLocalWidth(),
                            static_cast<float>(0.96 * parent_->getSize().y) / game_over_background->GetLocalHeight());

  tile_size = game_background->GetWidth() / width_of_net_in_tiles;
  height_of_net_in_tiles = game_background->GetHeight() / tile_size;
  indent_by_x = tile_size / 7;

  red_line.setSize(sf::Vector2f(game_background->GetWidth(),
                                game_background->GetHeight() - tile_size * height_of_net_in_tiles));
  red_line.setPosition(indent_x, indent_y + tile_size * height_of_net_in_tiles);
  red_line.setFillColor(sf::Color(255, 0, 0));

  white_line.setSize(sf::Vector2f(parent_->getSize().x * 0.4, 5));
  white_line.setFillColor(my_white);

  figures_pos =
      {
          {{-tile_size, 0}, {-2 * tile_size, 0}, {0, 0}, {tile_size, 0}},
          {{-tile_size, -tile_size}, {0, -tile_size}, {-tile_size, 0}, {0, 0}},
          {{-tile_size, 0}, {-tile_size, tile_size}, {0, 0}, {0, -tile_size}},
          {{0, 0}, {-tile_size, 0}, {0, tile_size}, {-tile_size, -tile_size}},
          {{0, 0}, {0, -tile_size}, {0, tile_size}, {-tile_size, -tile_size}},
          {{0, 0}, {0, -tile_size}, {0, tile_size}, {tile_size, -tile_size}},
          {{0, 0}, {0, -tile_size}, {0, tile_size}, {-tile_size, 0}}
      };
  figures.resize(figures_pos.size(), std::vector<sf::RectangleShape>(figures_pos[0].size()));
  for (size_t i = 0; i < figures.size(); ++i) {
    for (size_t j = 0; j < figures[i].size(); ++j) {
      figures[i][j].setSize(sf::Vector2f(1, 1));
      figures[i][j].setPosition(figures_pos[i][j].x + static_cast<int>(width_of_net_in_tiles / 2 * tile_size),
                                figures_pos[i][j].y + tile_size);
    }
  }
  type_of_figure = std::rand() % figures.size();
  figure = {figures[type_of_figure], figures[type_of_figure].size(), type_of_figure};
  type_of_figure = std::rand() % figures.size();
  next_figure = {figures[type_of_figure], figures[type_of_figure].size(), type_of_figure};

  color = GetRandomColor();
  next_color = GetRandomColor();

  speed_of_falling = 1;
  moves_by_x = 0;
  moves_by_y = 0;
  rotation = 0;
  sf::Event event;
  SetKeyPressedEvent( [this](const sf::Event& event){ CheckEvents(event); });

  is_tiled.resize(height_of_net_in_tiles + 2,
                  std::vector<bool>(width_of_net_in_tiles + 2, false));
  is_destroyed.resize(height_of_net_in_tiles + 2,
                      std::vector<bool>(width_of_net_in_tiles + 2, false));
  supposed_to_be_destroyed.resize(height_of_net_in_tiles + 2,
                                  std::vector<bool>(width_of_net_in_tiles + 2, false));
  mem_color.resize(height_of_net_in_tiles + 2,
                   std::vector<sf::Color>(width_of_net_in_tiles + 2, my_white));

  record = GetRecord();
  coins = 0;

  main_font.loadFromFile(PATH_TO_RESOURCES"/Game1/fonts/main_font.ttf");

  SetText(record_text, main_font, "Record", 50, my_green,
          {static_cast<float>(game_background->GetWidth() * 1.40),
           static_cast<float>(game_background->GetHeight() * 0.13)});
  SetText(record_value, main_font, std::to_string(record), 50, my_orange,
          {static_cast<float>(game_background->GetWidth() * 1.40),
           static_cast<float>(game_background->GetHeight() * 0.06)});
  SetText(score_text, main_font, "Score", 50, my_blue,
          {static_cast<float>(game_background->GetWidth() * 1.20),
           static_cast<float>(game_background->GetHeight() * 0.31)});
  SetText(coins_text, main_font, "Coins", 50, my_orange,
          {static_cast<float>(game_background->GetWidth() * 1.65),
           static_cast<float>(game_background->GetHeight() * 0.31)});
  SetText(new_text, main_font, "New", 50, my_orange,
          {static_cast<float>(game_background->GetWidth() * 1.45),
           static_cast<float>(game_background->GetHeight() * 0.71)});
  SetText(back_text, main_font, "Back", 100, my_orange,
          {static_cast<float>(game_background->GetWidth() * 1.35),
           static_cast<float>(game_background->GetHeight() * 0.85)});
  SetText(restart_text, main_font, "Restart", 100, my_blue,
          {static_cast<float>(game_background->GetWidth() * 1.27),
           static_cast<float>(game_background->GetHeight() * 0.50)});
  SetText(game_over_text, main_font, "I'm still hungry:(", 50, my_orange,
          {static_cast<float>(game_background->GetWidth() * 0.28),
           static_cast<float>(game_background->GetHeight() * 0.20)});

}

void Game1::SetText(sf::Text& target, const sf::Font& font, const std::string& text, int character_size,
                    sf::Color my_color, sf::Vector2f pos) {
  target.setFont(font);
  target.setString(text);
  target.setCharacterSize(character_size);
  target.setFillColor(my_color);
  target.setPosition(pos);
}

int Game1::GetRecord() {
  std::ifstream record_file;
  record_file.open(PATH_TO_RESOURCES"/Game1/data_files/record.txt");
  char ch;
  std::string my_record;
  if (record_file.is_open()) {
    while (record_file.good()) {
      record_file >> ch;
      my_record += ch;
    }
  }
  my_record.erase(my_record.size() - 1, 1);
  record_file.close();
  return std::stoi(my_record);
}

void Game1::SetRecord(int my_record, int my_score) {
  int new_record = std::max(my_record, my_score);
  std::ofstream record_file;
  record_file.open(PATH_TO_RESOURCES"/Game1/data_files/record.txt");
  record_file << std::to_string(new_record);
  record_file.close();
}

sf::Color Game1::GetRandomColor() {
  return sf::Color(rand() % 256, rand() % 256, rand() % 256);
}

void Game1::CheckEvents(const sf::Event& event) {
  if (event.type == sf::Event::KeyPressed and
      (event.key.code == sf::Keyboard::Key::Left or event.key.code == sf::Keyboard::Key::A)) {
    moves_by_x = -1;
  }
  if (event.type == sf::Event::KeyPressed and
      (event.key.code == sf::Keyboard::Key::Right or event.key.code == sf::Keyboard::Key::D)) {
    moves_by_x = 1;
  }
  if (event.type == sf::Event::KeyPressed and
      (event.key.code == sf::Keyboard::Key::Down or event.key.code == sf::Keyboard::Key::S)) {
    for (size_t i = 0; i < figure.size; ++i) {
      if (figure.tiles[i].getPosition().y < game_background->GetHeight() - tile_size) {
        moves_by_y = 1;
      }
    }
  }
  if (event.type == sf::Event::KeyPressed and
      (event.key.code == sf::Keyboard::Key::Up or event.key.code == sf::Keyboard::Key::W)) {
    rotation = 1;
  }
}

void Game1::DestroyRow(int i, int j) {
  if (transparency == start_transparency) {
    //row_destroying_sound.play();
  }
  transparency -= speed_of_destruction * speed_of_falling;
  if (transparency < 2) {
    transparency = start_transparency;
    supposed_to_be_destroyed[i][j] = false;
    in_process_of_destruction = false;
  }
  sf::RectangleShape white_row(sf::Vector2f(game_background->GetWidth(), tile_size));
  white_row.setPosition(indent_x + 1, indent_y + 1 + i * tile_size);
  white_row.setFillColor(sf::Color(255, 255, 255, transparency));
  parent_->draw(white_row);
}

void Game1::ReloadNet() {
  for (int i = 0; i < height_of_net_in_tiles; ++i) {
    for (int j = 0; j < width_of_net_in_tiles; ++j) {
      is_tiled[i][j] = false;
    }
  }
  type_of_figure = std::rand() % figures.size();
  figure = {figures[type_of_figure], figures[type_of_figure].size(), type_of_figure};
  score = 0;
  speed_of_falling = 1;
}

void Game1::Draw() {
  background->Draw();
  game_background->Draw();
  for (int i = 0; i < height_of_net_in_tiles; ++i) {
    for (int j = 0; j < width_of_net_in_tiles; ++j) {
      tile.setPosition(indent_x + j * tile_size, indent_y + i * tile_size);
      parent_->draw(tile);
    }
  }
  parent_->draw(red_line);

  white_line.setPosition(game_background->GetWidth() * 2 * (0.5 + 0.02 + (1 - 0.5 - 0.02 - 0.4) / 2.),
                         0.05 * game_background->GetHeight());
  parent_->draw(white_line);
  white_line.setPosition(game_background->GetWidth() * 2 * (0.5 + 0.02 + (1 - 0.5 - 0.02 - 0.4) / 2.),
                         0.22 * game_background->GetHeight());
  parent_->draw(white_line);
  white_line.setPosition(game_background->GetWidth() * 2 * (0.5 + 0.02 + (1 - 0.5 - 0.02 - 0.4) / 2.),
                         0.4 * game_background->GetHeight());
  parent_->draw(white_line);
  white_line.setPosition(game_background->GetWidth() * 2 * (0.5 + 0.02 + (1 - 0.5 - 0.02 - 0.4) / 2.),
                         0.8 * game_background->GetHeight());
  parent_->draw(white_line);

  for (size_t i = 0; i < figure.size; ++i) {
    sf::RectangleShape figure_tile(sf::Vector2f(tile_size - 2, tile_size - 2));
    figure_tile.setPosition(indent_x + 1 + figure.tiles[i].getPosition().x,
                            indent_y + 1 + figure.tiles[i].getPosition().y);
    figure_tile.setFillColor(color);
    parent_->draw(figure_tile);
  }

  if (!is_active_game_over) {
    for (size_t i = 0; i < next_figure.size; ++i) {
      sf::RectangleShape figure_tile(sf::Vector2f(tile_size - 2, tile_size - 2));
      figure_tile.setPosition(next_figure.tiles[i].getPosition().x +
                                  1.18 * game_background->GetWidth() - tile_size * next_figure.size / 2,
                              next_figure.tiles[i].getPosition().y + 0.6 * game_background->GetHeight() -
                                  tile_size * next_figure.size / 2);
      figure_tile.setFillColor(next_color);
      parent_->draw(figure_tile);
    }
  }

  //maintain bottom correct
  for (int i = 0; i < height_of_net_in_tiles; ++i) {
    for (int j = 0; j < width_of_net_in_tiles; ++j) {
      if (is_destroyed[i][j]) {
        supposed_to_be_destroyed[i][j] = true;
        in_process_of_destruction = true;
        row_of_destruction = i;
      }
      if (supposed_to_be_destroyed[i][j]) {
        DestroyRow(i, j);
      }
      if (is_tiled[i][j] && !in_process_of_destruction) {
        sf::RectangleShape figure_tile(sf::Vector2f(tile_size - 2, tile_size - 2));
        figure_tile.setPosition(indent_x + 1 + j * tile_size, indent_y + 1 + i * tile_size);
        figure_tile.setFillColor(mem_color[i][j]);
        parent_->draw(figure_tile);
      }
      if (is_tiled[i][j] and in_process_of_destruction) {
        if (i <= row_of_destruction) {
          sf::RectangleShape figure_tile(sf::Vector2f(tile_size - 2, tile_size - 2));
          figure_tile.setPosition(indent_x + 1 + j * tile_size, indent_y + 1 + (i - 1) * tile_size);
          figure_tile.setFillColor(mem_color[i][j]);
          parent_->draw(figure_tile);
        }
        if (i > row_of_destruction) {
          sf::RectangleShape figure_tile(sf::Vector2f(tile_size - 2, tile_size - 2));
          figure_tile.setPosition(indent_x + 1 + j * tile_size, indent_y + 1 + i * tile_size);
          figure_tile.setFillColor(mem_color[i][j]);
          parent_->draw(figure_tile);
        }
      }
    }
  }

  SetText(score_value, main_font, std::to_string(score), 50, my_white,
          {static_cast<float>(game_background->GetWidth() * 1.20),
           static_cast<float>(game_background->GetHeight() * 0.24)});
  SetText(coins_value, main_font, std::to_string(coins), 50, my_white,
          {static_cast<float>(game_background->GetWidth() * 1.65),
           static_cast<float>(game_background->GetHeight() * 0.24)});

  parent_->draw(record_text);
  parent_->draw(record_value);
  parent_->draw(score_text);
  parent_->draw(score_value);
  parent_->draw(coins_text);
  parent_->draw(coins_value);
  parent_->draw(back_text);
  if (!is_active_game_over) {
    parent_->draw(new_text);
  }

  if (is_active_game_over) {
    game_over_background->Draw();
    parent_->draw(restart_text);
    parent_->draw(game_over_text);
  }
}

void Game1::Update(double dt) {
  tile_size = game_background->GetWidth() / width_of_net_in_tiles;
  height_of_net_in_tiles = game_background->GetHeight() / tile_size;

  tile.setSize(sf::Vector2f(tile_size, tile_size));
  tile.setFillColor(my_transparent);
  tile.setOutlineThickness(1);
  tile.setOutlineColor(my_skyblue);

  Figure prev_figure = figure;

  // move by x
  for (size_t i = 0; i < figure.size; ++i) {
    sf::Vector2f current_position = figure.tiles[i].getPosition();
    figure.tiles[i].setPosition(current_position.x + moves_by_x * tile_size, current_position.y);
    if (figure.tiles[i].getPosition().x < 0 or
        figure.tiles[i].getPosition().x > game_background->GetWidth() - tile_size or
        is_tiled[(static_cast<int>(figure.tiles[i].getPosition().y) +
            indent_by_x) / tile_size][static_cast<int>(figure.tiles[i].getPosition().x) / tile_size] or
        is_tiled[static_cast<int>(figure.tiles[i].getPosition().y) /
            tile_size + 1][static_cast<int>(figure.tiles[i].getPosition().x) / tile_size]) {
      figure = prev_figure;
      break;
    }
  }

  // move by y
  for (size_t i = 0; i < figure.size; ++i) {
    if (is_tiled[static_cast<int>(figure.tiles[i].getPosition().y) /
        tile_size + 1][static_cast<int>(figure.tiles[i].getPosition().x) / tile_size] or
        figure.tiles[i].getPosition().y > game_background->GetHeight() - tile_size) {
      //gl.figure_placing_sound.play()
      if (static_cast<int>(figure.tiles[i].getPosition().y) / tile_size + 1 == is_tiled.size()) {
        is_tiled[static_cast<int>(figure.tiles[i].getPosition().y) /
        tile_size][static_cast<int>(figure.tiles[i].getPosition().x) / tile_size] = true;
      }
      for (int j = 0; j < figure.size; ++j) {
        is_tiled[static_cast<int>(figure.tiles[j].getPosition().y) /
            tile_size][static_cast<int>(figure.tiles[j].getPosition().x) / tile_size] = true;
      }
      for (int j = 0; j < figure.size; ++j) {
        mem_color[static_cast<int>(figure.tiles[j].getPosition().y) /
            tile_size][static_cast<int>(figure.tiles[j].getPosition().x) / tile_size] = color;
      }
      color = next_color;
      figure = next_figure;
      next_color = GetRandomColor();
      type_of_figure = std::rand() % figures.size();
      next_figure = {figures[type_of_figure], figures[type_of_figure].size(), type_of_figure};
      break;
    }
    sf::Vector2f current_position = figure.tiles[i].getPosition();
    figure.tiles[i].setPosition(current_position.x,
                                current_position.y + moves_by_y * tile_size + speed_of_falling);
  }

  // rotation
  sf::RectangleShape center_of_rotation = figure.tiles[0];
  if (rotation == 1 && figure.type != 1) {
    for (size_t i = 0; i < figure.size; ++i) {
      int difference_x = figure.tiles[i].getPosition().y - center_of_rotation.getPosition().y;
      int difference_y = figure.tiles[i].getPosition().x - center_of_rotation.getPosition().x;
      sf::Vector2f current_position = figure.tiles[i].getPosition();
      figure.tiles[i].setPosition(center_of_rotation.getPosition().x - difference_x,
                                  center_of_rotation.getPosition().y + difference_y);
      if (figure.tiles[i].getPosition().x < 0 or
          figure.tiles[i].getPosition().x > game_background->GetWidth() - tile_size or
          is_tiled[static_cast<int>(figure.tiles[i].getPosition().y) /
              tile_size + 1][static_cast<int>(figure.tiles[i].getPosition().x) / tile_size] or
          figure.tiles[i].getPosition().y > game_background->GetHeight() - tile_size) {
        figure = prev_figure;
        break;
      }
    }
  }

  // return to base
  moves_by_x = 0;
  moves_by_y = 0;
  rotation = 0;

  // find destroyed rows
  int current_row = height_of_net_in_tiles - 1;
  int destroyed_rows = 0;
  for (int i = 0; i < height_of_net_in_tiles - 1; ++i) {
    int row = height_of_net_in_tiles - 1 - i;
    int number_of_tiled_in_row = 0;
    for (int j = 0; j < width_of_net_in_tiles; ++j) {
      if (is_tiled[row][j]) {
        number_of_tiled_in_row += 1;
      }
      is_tiled[current_row][j] = is_tiled[row][j];
      mem_color[current_row][j] = mem_color[row][j];
    }
    if (number_of_tiled_in_row < width_of_net_in_tiles) {
      current_row -= 1;
      for (int j = 0; j <width_of_net_in_tiles; ++j) {
        is_destroyed[row][j] = false;
      }
    }
    else {
      destroyed_rows += 1;
      counter_of_destructed_rows += 1;
      if (counter_of_destructed_rows == max_value_before_speed_up) {
        counter_of_destructed_rows = 0;
        speed_of_falling += 1;
      }
      is_destroyed[current_row][0] = true;
    }
  }
  score += destroyed_rows * width_of_net_in_tiles * one_tile_cost;
  coins += destroyed_rows * width_of_net_in_tiles * one_tile_cost / 100;

  //game over
  for (int col = 0; col < width_of_net_in_tiles; ++col) {
    if (is_tiled[1][col]) {
      is_active_game_over = true;
      //game_over_sound.play()
    }
  }
  if (is_active_game_over) {
    SetRecord(record, score);
    ReloadNet();
    //pygame.mixer.music.pause()
  }

}

void Game1::cont() {
  SetEnableMod(false);
}

void Game1::stop(){
  SetEnableMod(true);
}

Game1* Game1::game_1_pointer = nullptr;

Game1* Game1::GetGame1() {
  if (game_1_pointer == nullptr) {
    game_1_pointer = new Game1();
  }
  return game_1_pointer;
}

Game1::~Game1() {
  background->Delete();
  game_background->Delete();
}
