//#include <TileMapEditor.hpp>
//#include <SFML/Graphics/RenderWindow.hpp>
//
//TileMapEditor::TileMapEditor(const std::string& layergroup)
//	: mTileManager(layergroup)
//{
//
//}
//
//void TileMapEditor::loadTileGroup(const std::string& layergroup)
//{
//	mTileManager.loadTileGroup(layergroup);
//}
//
//void TileMapEditor::frame(sf::RenderWindow& window, sf::Time dt)
//{
//	ImGui::Begin("Map Editor");
//
//	if (ImGui::Button("owo what's this"))
//	{
//		window.setTitle("N-Nani!?");
//	}
//
//	ImGui::End();
//}
//
//void TileMapEditor::draw(sf::RenderTarget& target, sf::RenderStates states) const
//{
//	target.draw(mTileManager, states);
//	target.draw(mTileManager, states);
//}