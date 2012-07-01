#include <boost/program_options/errors.hpp>
#include <boost/program_options/parsers.hpp>
#include <boost/program_options/option.hpp>
#include <boost/program_options/options_description.hpp>
#include <boost/program_options/variables_map.hpp>
#include <boost/smart_ptr.hpp>

#include <iostream>

#include <QApplication>
#include <QDebug>
#include <QFile>
#include <QGraphicsItem>
#include <QGraphicsView>
#include <QPainter>
#include <QString>
#include <QStringList>
#include <QTextStream>

#include "canvas.h"
#include "colormap.h"
#include "word.h"

namespace po = boost::program_options;

int main(int argc, char **argv)
{   
  std::string outfile, textfile;
  po::options_description desc("Allowed options");
  std::vector<std::string> orbargs;
  desc.add_options()
    ("help,h", "produce help message")
    ("debug,d", "run in debug mode")
    ("words,w",
     po::value<std::string>(&textfile)->required(),
     "input file with words to use in cloud")
    ("output,o",
     po::value<std::string>(&outfile)->default_value("cloud.png"), 
     "filename for output image file");

  // parse options
  po::variables_map vmap;
  try
    {
      po::store(po::command_line_parser(argc, argv).
		options(desc).run(), vmap);
      po::notify(vmap);      
    }
  catch(po::unknown_option &e)
    {
      std::cout << e.what() << " - aborting!" << std::endl;
      std::cout << desc << std::endl;
      return 1;
    }
  catch(po::error &e) // other errors
    {  
      // did the user actually just ask for help?
      if (vmap.count("help")) goto show_help;
      std::cout << e.what() << " - aborting!" << std::endl;
      return 1;
    }
  
  // does our user need any help?
  if (vmap.count("help")) 
    {
    show_help:
      std::cout << desc << std::endl;
      return 0;
    }

  QFile file(QString::fromStdString(textfile));
  if (!file.open(QIODevice::ReadOnly)) 
    std::cerr << "Could not read from file " << textfile << "." << std::endl;

  QApplication app(argc, argv);
  Canvas canvas;
  canvas.setBackgroundBrush(Qt::black);
  QGraphicsView view(&canvas);

  QTextStream stream(&file); 
  QStringList stringlist;
  while (!stream.atEnd() && stream.status() == QTextStream::Ok)
    {
      QString line = stream.readLine();
      stringlist.append(line.split(' '));
    }
  file.close();

  QVector<QColor> colormap = Colormap::coolColormap(10);
  
  // create words from strings and put them in wordlist
  int counter = 0;
  QList<Word*> wordlist;
  for (int i = 0; i < stringlist.size(); ++i)
    {
      QString s = stringlist[i];
      if (!s.isEmpty())
	{
	  Word *w = new Word(s);
	  w->setBrush(colormap[counter % 10]);
	  w->setFontSize(10 + 20*exp(-counter/5+1));
	  wordlist.push_back(w);
	  counter++;
	}
    }

  canvas.setWordList(wordlist);
  canvas.createLayout();
  
   // create image
  QImage img(800, 600, QImage::Format_ARGB32_Premultiplied);
  QPainter painter(&img);
  canvas.render(&painter);  
  if (vmap.count("debug")) 
    {
      foreach (QGraphicsItem *i, canvas.items())
	{
	  painter.setPen(((Word*)i)->brush().color());
	  ((Word*)i)->setBoundingRegionGranularity(.4);
	  foreach (QRect rect, i->boundingRegion(i->sceneTransform()).rects())
	    painter.drawRect(rect);
	}

    }
  painter.end();
 
  // save image
  img.save(QString::fromStdString(outfile));  
  
  view.show();
  return app.exec();
}
