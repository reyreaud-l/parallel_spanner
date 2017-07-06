#include "loader.hh"


Graph<> Loader::Load(std::string filename)
{
   std::ifstream in;
   in.open(filename);
   auto mygraph = Graph<>();
   std::string line;
   while (std::getline(in, line))
   {
      auto vertice = boost::add_vertex(mygraph);
      auto& data = mygraph[vertice];
      std::istringstream line_stream;
      std::string curr_string;
      line_stream.str(line);
      std::getline(line_stream, curr_string);
      data.name = curr_string;
      std::getline(line_stream, curr_string);
      data.x = std::stoi(curr_string);
      std::getline(line_stream, curr_string);
      data.y = std::stoi(curr_string);
   }
   in.close();
   return mygraph;
}
