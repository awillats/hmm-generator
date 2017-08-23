/*
 * Copyright (C) 2011 Georgia Institute of Technology, University of Utah,
 * Weill Cornell Medical College
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation, either version 3 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/*
 * This is a template implementation file for a user module derived from
 * DefaultGUIModel with a custom GUI.
 */

//#include <string.h>


#include "hmm_generator.h"
#include <iostream>
#include <main_window.h>




extern "C" Plugin::Object*
createRTXIPlugin(void)
{
  return new HmmGenerator();
}

static DefaultGUIModel::variable_t vars[] = {
  {
    "GUI label", "Tooltip description",
    DefaultGUIModel::PARAMETER | DefaultGUIModel::DOUBLE,
  },
  {
    "A State", "Tooltip description", DefaultGUIModel::STATE,
  },

};

static size_t num_vars = sizeof(vars) / sizeof(DefaultGUIModel::variable_t);

HmmGenerator::HmmGenerator(void)
  : DefaultGUIModel("HmmGenerator with Custom GUI", ::vars, ::num_vars)
{
  setWhatsThis("<p><b>HmmGenerator:</b><br>QWhatsThis description.</p>");
  DefaultGUIModel::createGUI(vars,
                             num_vars); // this is required to create the GUI
  customizeGUI();
  initParameters();
  update(INIT); // this is optional, you may place initialization code directly
                // into the constructor
  refresh();    // this is required to update the GUI with parameter and state
                // values
  QTimer::singleShot(0, this, SLOT(resizeMe()));
}

HmmGenerator::~HmmGenerator(void)
{
}

void
HmmGenerator::execute(void)
{
  return;
}

void
HmmGenerator::initParameters(void)
{
  some_parameter = 0;
  some_state = 0;

  BabyClass foobar(10,1);
  some_state = foobar.getFoo();

  V={10,5};
    std::vector<double> vFr = {0.1, 0.6};
    std::vector<double> vTr = {0.1, 0.1};
    
    int numElements = 350;
    std::vector<int> q = genHMM(vFr,vTr,numElements);
}

void
HmmGenerator::update(DefaultGUIModel::update_flags_t flag)
{
  switch (flag) {
    case INIT:
      period = RT::System::getInstance()->getPeriod() * 1e-6; // ms
      setParameter("GUI label", some_parameter);
      setState("A State", some_state);

      break;

    case MODIFY:
      some_parameter = getParameter("GUI label").toDouble();
//      some_state = time_var.getHour();
//      setState("A State", some_state);
      //time_var.incrTime(0,1,0);
      break;

    case UNPAUSE:
      break;

    case PAUSE:
      break;

    case PERIOD:
      period = RT::System::getInstance()->getPeriod() * 1e-6; // ms
      break;

    default:
      break;
  }
}

void
HmmGenerator::customizeGUI(void)
{
  QGridLayout* customlayout = DefaultGUIModel::getLayout();

  QGroupBox* button_group = new QGroupBox;

  QPushButton* abutton = new QPushButton("Button A");
  QPushButton* bbutton = new QPushButton("Button B");
  QHBoxLayout* button_layout = new QHBoxLayout;
  button_group->setLayout(button_layout);
  button_layout->addWidget(abutton);
  button_layout->addWidget(bbutton);
  QObject::connect(abutton, SIGNAL(clicked()), this, SLOT(aBttn_event()));
  QObject::connect(bbutton, SIGNAL(clicked()), this, SLOT(bBttn_event()));

  customlayout->addWidget(button_group, 0, 0);
  setLayout(customlayout);
}

// functions designated as Qt slots are implemented as regular C++ functions
void
HmmGenerator::aBttn_event(void)
{
}

void
HmmGenerator::bBttn_event(void)
{
}