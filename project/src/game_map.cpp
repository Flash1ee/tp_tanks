#include "game_map.hpp"

#include <fstream>
#include <iostream>

auto block_size = 8;
std::map<char, entities> map_entity = {{'.', EMPTY}, {'#', WALL}};

std::map<char, std::vector<float>> coords = {
    {'.',
     {256, 0, static_cast<float>(block_size), static_cast<float>(block_size)}},
    {'#',
     {336, 0, static_cast<float>(block_size), static_cast<float>(block_size)}}};

void Map::set_pos(size_t i, size_t j, std::shared_ptr<Object> p) {
    if (i >= m_rows || j >= m_cols) {
        throw std::invalid_argument("Bad position");
    }
    m_field[i][j] = p;
    return;
}
sf::Sprite Map::getSprite() const { return this->sprite; }

Map::Map(std::string map, std::string sprite) : m_block_size(block_size) {
    if (map.empty() || sprite.empty()) {
        throw std::invalid_argument("Bad stream");
    }
    std::ifstream in(map);
    if (!in.is_open()) {
        throw std::runtime_error("Can't open map file");
    }
    in >> m_rows >> m_cols;
    if (!m_rows || !m_cols) {
        throw "Empty play field";
    }

    m_field.resize(m_rows);
    for (auto& row : m_field) {
        row.resize(m_cols);
    }

    std::string line;
    for (size_t i = 0; i < m_rows; i++) {
        in >> line;
        for (size_t j = 0; j < m_cols; j++) {
            char cur = line[j];
            if (!map_entity.count(cur)) {
                throw std::invalid_argument("Unknown map entity");
            }
            std::vector<float> cord = coords[cur];
            auto p = std::make_shared<Object>(sprite, i, j, cord[0], cord[1], cord[2], cord[3]);
            set_pos(i, j, p);
        }
    }
    if (!in.eof()) {
        throw "read error, not found eof";
    }
    in.close();
}
void Map::drawMap(sf::RenderWindow &window) {
  for (auto row = 0; row < m_rows; row++) {
    for (auto cols = 0; cols < m_cols; cols++) {
      window.draw(m_field[row][cols]->getSprite());
    }
  }
}