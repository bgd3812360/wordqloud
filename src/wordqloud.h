#ifndef WORDQLOUD_H_
#define WORDQLOUD_H_

#include <QMainWindow>
#include "enumerations.h"

class Canvas;
class QAction;
class QActionGroup;
class QGraphicsView;
class QLabel;
class QMenu;
class QPushButton;
class QProgressBar;
class QToolBar;
class View;

class WordQloud : public QMainWindow
{
  Q_OBJECT

  public:
  WordQloud();

  public slots:
  void onProgressChanged(int, int);

protected:
  void renderImage();
		    
private slots:
  void about();
  void createCloudBoundsFromImage();
  void load();
  void onClearWordListActionTriggered();
  void onLoadColourSchemeActionTriggered();
  void onLoadWordlist();  
  void onOrientationActionTriggered(QAction*);
  void onColourschemeActionGroupTriggered(QAction*);
  void onColourVariationActionTriggered(QAction*);
  void onHAlignActionTriggered();
  void onHDistributeActionTriggered();  
  void onLayoutBoundsActionTriggered(QAction*);
  void onLayoutEnded();
  void onLayoutStarted();
  void onPathGroupActionTriggered(QAction*);
  void onSaveActionTriggered();
  void onSaveColourSchemeActionTriggered();
  void onSceneRectActionTriggered();
  void onUnpinAllButtonClicked();
  void onVDistributeActionTriggered();
  void reCreateLayout();
  void saveBitmap();
  void savePDF();  
  void setBackgroundColor();
  void setCustomScheme();
  void setFont();
  void spinColours();
  void spinOrientations();  
  void onStatusChanged(QString);
  void onStopButtonClicked();
  void onVAlignActionTriggered();
private:
  void addColourVariations(QList<QColor> &colourlis, ColourVariation v);
  ColourVariation checkedColourVariation();
  void createActions();
  void createMenus();
  void createToolbar();
  void createColourschemeMenu();
  QIcon createColourschemeIcon(QVector<QColor> colours);
  QList<QColor> checkedColourscheme();

  QMenu *fileMenu;
  QMenu *layoutMenu;
  QMenu *helpMenu;
  
  QAction *customColourschemeAction;
  QActionGroup *alignmentGroup;
  QPushButton *unpinAllButton;
  QPushButton *spinColoursButton;
  QPushButton *spinOrientationsButton;  
  QPushButton *reCreateLayoutButton;
  QActionGroup *colourschemeActionGroup;
  QAction *aboutAction;
  QAction *backgroundColorAction;
  QAction *clearWordListAction;
  QAction *exitAction;
  QAction *fontAction;
  QAction *loadAction;
  QAction *loadColourSchemeAction;
  QAction *loadWordlistAction;
  QAction *saveAction;
  QAction *saveColourSchemeAction;
  QAction *savePngAction;
  QAction *saveSvgAction;  
  QAction *boundsFromImageAction;

  QActionGroup *pathGroup;
  QAction *spiralPathAction;
  QAction *rectPathAction;

  QActionGroup *layoutBoundsActionGroup;
  QAction *sceneBoundOnlyAction;
  QAction *imageBoundOnlyAction;
  QAction *imageAndSceneBoundAction;    

  QAction *sceneRectAction;

  QActionGroup *orientationActionGroup;
  QAction *anyOrientationAction;
  QAction *horizontalOrientationAction;
  QAction *mostlyHorizontalOrientationAction;
  QAction *halfAndHalfOrientationAction;
  QAction *mostlyVerticalOrientationAction;
  QAction *verticalOrientationAction;
    
  QActionGroup *colourVariationActionGroup;
  QAction *asPaletteAction;
  QAction *littleVariationAction;
  QAction *someVariationAction;
  QAction *lotsOfVariationAction;
  QAction *wildVariationAction;

  QToolBar *toolbar;

  View *view;
  Canvas *canvas;
  QProgressBar *progressBar;
  QPushButton *stopLayoutButton;
};

#endif
