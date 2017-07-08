#include "loader.hh"


Graph<> Loader::load_graph(std::string filename)
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
      std::getline(line_stream, curr_string, ',');
      data.name = curr_string;
      std::getline(line_stream, curr_string, ',');
      data.x = std::stoi(curr_string);
      std::getline(line_stream, curr_string, ',');
      data.y = std::stoi(curr_string);
   }
   in.close();
   return mygraph;
}

std::vector<Point> Loader::load_point(std::string filename)
{
   std::ifstream in;
   in.open(filename);
   std::vector<Point> res;
   std::string line;
   while (std::getline(in, line))
   {
      Point p;
      std::istringstream line_stream;
      std::string curr_string;
      line_stream.str(line);
      std::getline(line_stream, curr_string, ',');
      std::getline(line_stream, curr_string, ',');
      p.x = std::stoi(curr_string);
      std::getline(line_stream, curr_string, ',');
      p.y = std::stoi(curr_string);
      res.push_back(p);
   }
   in.close();
   return res;
}
