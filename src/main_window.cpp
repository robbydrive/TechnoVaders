#include "main_window.hpp"

#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QFormLayout>
#include <iostream>

typedef void (QWidget::*QWidgetVoidSlot)();

MainWindow::MainWindow()
{
  // TO DO: more styling
  TSettings loadedSettings = LoadSettings();
  setFixedSize(600, 600);
  QPushButton * launchButton = new QPushButton("Launch", m_mainWidget);
  QPushButton * settingsButton = new QPushButton("Settings", m_mainWidget);
  QPushButton * exitButton = new QPushButton("Exit", m_mainWidget);
  launchButton->move(250, 200);
  settingsButton->move(250, 270);
  exitButton->move(250, 340);
  connect(launchButton, SIGNAL(clicked()), this, SLOT(OnMainLaunchClicked()));
  connect(settingsButton, SIGNAL(clicked()), this, SLOT(OnMainSettingsClicked()));
  connect(exitButton, SIGNAL(clicked()), this, SLOT(OnMainExitClicked()));

  QPushButton * backButton = new QPushButton("Back", m_settingsWidget);
  backButton->move(0, 0);
  connect(backButton, SIGNAL(clicked()), this, SLOT(OnSettingsBackClicked()));
  // TO DO: add control settings
  QComboBox * difficultyChoice = new QComboBox(m_settingsWidget);
  difficultyChoice->setObjectName("difficulty");
  difficultyChoice->addItems({ "Low", "Medium", "High" });
  difficultyChoice->setCurrentText(QString(loadedSettings.find("Difficulty")->second.c_str()));
  QComboBox * resolutionChoice = new QComboBox(m_settingsWidget);
  resolutionChoice->setObjectName("resolution");
  resolutionChoice->addItems({ "640x480", "800x600", "1024x768", "Full screen"});
  resolutionChoice->setCurrentText(QString(loadedSettings.find("Resolution")->second.c_str()));
  QFormLayout * layout = new QFormLayout(m_settingsWidget);
  layout->addRow("Resolution", resolutionChoice);
  layout->addRow("Difficulty", difficultyChoice);
  layout->setFormAlignment(Qt::AlignHCenter | Qt::AlignCenter);

  m_stack->addWidget(m_mainWidget);
  m_stack->addWidget(m_settingsWidget);
  m_stack->setCurrentIndex(0);
  setCentralWidget(m_stack);

  setFocusPolicy(Qt::StrongFocus);
}