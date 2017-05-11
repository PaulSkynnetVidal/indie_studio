#include "MenuCore.hh"

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

bomber::MenuCore::MenuCore()
: _device(0), _driver(0), _smgr(0), _guienv(0), _start(false), _secondPlayer(false) {}

bomber::MenuCore::~MenuCore()
{
}

void	bomber::MenuCore::init()
{
  if ((_device = irr::createDevice(irr::video::EDT_OPENGL,
				   irr::core::dimension2d<irr::u32>(MENU_DIM('x'), MENU_DIM('y')),
				   DEFAULT_BPP, false, false, false, this)) == NULL
      || (_driver = _device->getVideoDriver()) == NULL
      || (_smgr = _device->getSceneManager()) == NULL
      || (_guienv = _device->getGUIEnvironment()) == NULL)
    throw 1;
  son.Play_Sound("./src/sono/menu.wav");
  _device->setWindowCaption(MENU_TITLE);
  _start = false;
}

void	bomber::MenuCore::clear()
{
  son.Stop();
  _device->drop();
  _nMenu.clear();
}

void	bomber::MenuCore::update()
{

}

void	bomber::MenuCore::draw()
{
  if (_device->isWindowActive())
    {
      _driver->beginScene(false, true, irr::video::SColor(0,0,0,0));
      _smgr->drawAll();
      _guienv->drawAll();
      _driver->endScene();
    }
  else
    _device->yield();
}

void	bomber::MenuCore::Creat_Menu()
{
  ITexture *menu;
  menu = _driver->getTexture("obj/texture/Menu_de_Jeu_sans_bouton.png");
  IGUIImage *img;
  img = _guienv->addImage(core::rect<s32>(0,0,800,600));
  img->setImage(menu);
  img->setScaleImage(true);
  _driver->removeTexture(menu);
  // MAIN
  IGUIButton *btn = _guienv->addButton(core::rect<int>(280, 200, 520, 280), 0, 3);
  btn->setImage(_driver->getTexture("obj/texture/button//bouton_menu_play.png"));
  btn->setPressedImage(_driver->getTexture("obj/texture/button/bouton_menu_play_focus.png"));
  _nMenu.push_back({btn, M_MAIN});
  IGUIButton *button2 = _guienv->addButton(core::rect<int>(280, 320, 520, 400), 0, 4);
  button2->setImage(_driver->getTexture("obj/texture/button//bouton_menu_option.png"));
  button2->setPressedImage(_driver->getTexture("obj/texture/button/bouton_menu_option_focus.png"));
  _nMenu.push_back({button2, M_MAIN});
  IGUIButton *button3 = _guienv->addButton(core::rect<int>(280, 440, 520, 520), 0, 5);
  button3->setImage(_driver->getTexture("obj/texture/button//bouton_menu_quitter.png"));
  button3->setPressedImage(_driver->getTexture("obj/texture/button/bouton_menu_quitter_focus.png"));
  _nMenu.push_back({button3, M_MAIN});
  IGUIButton *button4 = _guienv->addButton(core::rect<int>(538, 533, 700, 584), 0, 6);
  button4->setImage(_driver->getTexture("obj/texture/button/bouton_menu_credit.png"));
  button4->setPressedImage(_driver->getTexture("obj/texture/button/bouton_menu_credit_focus.png"));
  _nMenu.push_back({button4, M_MAIN});
  IGUIButton *button5 = _guienv->addButton(core::rect<int>(720, 533, 780, 585), 0, 7);
  button5->setImage(_driver->getTexture("obj/texture/button//bouton_sound_focus.png"));
  button5->setPressedImage(_driver->getTexture("obj/texture/button/bouton_sound_active.png"));
  _nMenu.push_back({button5, M_MAIN});
  // PLAY
  btn = _guienv->addButton(core::rect<int>(280, 200, 520, 280), 0, 10);
  btn->setImage(_driver->getTexture("obj/texture/button/bouton_menu_one_player.png"));
  btn->setPressedImage(_driver->getTexture("obj/texture/button/bouton_menu_one_player_focus.png"));
  _nMenu.push_back({btn, M_PLAY});
  btn = _guienv->addButton(core::rect<int>(280, 320, 520, 400), 0, 11);
  btn->setImage(_driver->getTexture("obj/texture/button/bouton_menu_two_player.png"));
  btn->setPressedImage(_driver->getTexture("obj/texture/button/bouton_menu_two_player_focus.png"));
  _nMenu.push_back({btn, M_PLAY});
  btn = _guienv->addButton(core::rect<int>(280, 440, 520, 520), 0, 12);
  btn->setImage(_driver->getTexture("obj/texture/button/bouton_menu_ia.png"));
  _nMenu.push_back({btn, M_PLAY});
  btn = _guienv->addButton(core::rect<int>(720, 533, 780, 585), 0, 8);
  btn->setImage(_driver->getTexture("obj/texture/button/bouton_fleche_retour.png"));
  btn->setPressedImage(_driver->getTexture("obj/texture/button/bouton_fleche_retour_focus.png"));
  _nMenu.push_back({btn, M_PLAY});
  // OPTION
  img = _guienv->addImage(core::rect<s32>(0,0,800,600));
  img->setImage(_driver->getTexture("obj/texture/Rules_And_Controls_sans_bouton.png"));
  img->setScaleImage(true);
  _nMenu.push_back({img, M_OPTION});
  btn = _guienv->addButton(core::rect<int>(720, 533, 780, 585), 0, 9);
  btn->setImage(_driver->getTexture("obj/texture/button/bouton_fleche_retour.png"));
  btn->setPressedImage(_driver->getTexture("obj/texture/button//bouton_fleche_retour_focus.png"));
  _nMenu.push_back({btn, M_OPTION});
  // CREDITS
  img = _guienv->addImage(core::rect<s32>(0,0,800,600));
  img->setImage(_driver->getTexture("obj/texture/credit_sans_bouton.png"));
  img->setScaleImage(true);
  _nMenu.push_back({img, M_CREDIT});
  btn = _guienv->addButton(core::rect<int>(20, 533, 80, 585), 0, 9);
  btn->setImage(_driver->getTexture("obj/texture/button/bouton_fleche_retour.png"));
  btn->setPressedImage(_driver->getTexture("obj/texture/button//bouton_fleche_retour_focus.png"));
  _nMenu.push_back({btn, M_CREDIT});
}

bool	bomber::MenuCore::run(std::string & map, bool & secondPlayer)
{
  init();
  Creat_Menu();
  map = "map";
  chooseMenu(M_MAIN);
  while(_device->run())
    {
      update();
      draw();
    }
  clear();
  secondPlayer = _secondPlayer;
  return _start;
}

void	bomber::MenuCore::chooseMenu(bomber::e_menu menu)
{
    for (size_t i = 0; i < _nMenu.size(); i++) {
      if (_nMenu[i].type != menu)
	_nMenu[i].btn->setVisible(false);
      else
	_nMenu[i].btn->setVisible(true);
    }
}

bool	bomber::MenuCore::isKeyPressed(irr::EKEY_CODE key, irr::SEvent const & event)
{
  if (event.EventType == irr::EET_KEY_INPUT_EVENT &&
      event.KeyInput.Key == key &&
      event.KeyInput.PressedDown == false)
    return true;
  return false;
}

bool	bomber::MenuCore::OnEvent(irr::SEvent const & event)
{
  if (!_device)
    return false;
  if (event.EventType == EET_GUI_EVENT)
    {
      s32 id = event.GUIEvent.Caller->getID();
      switch(id)
	{
	case 3:
	  if (event.GUIEvent.EventType == gui::EGET_BUTTON_CLICKED )
	    chooseMenu(M_PLAY);
	  break;
	case 4:
    	  if (event.GUIEvent.EventType == gui::EGET_BUTTON_CLICKED )
	    {
	      chooseMenu(M_OPTION);
	    }
	  break;
	case 5:
    	  if (event.GUIEvent.EventType == gui::EGET_BUTTON_CLICKED )
    	    {
	      _device->closeDevice();
	      _start = false;
	    }
	  break;
        case 6:
	  if (event.GUIEvent.EventType == gui::EGET_BUTTON_CLICKED )
	    chooseMenu(M_CREDIT);
	  break;
        case 7:
    	  if (event.GUIEvent.EventType == gui::EGET_BUTTON_CLICKED )
    	    {
	      // SOUND
	    }
	  break;
          case 8:
          if (event.GUIEvent.EventType == gui::EGET_BUTTON_CLICKED )
	    chooseMenu(M_MAIN);
    	  break;
        case 9:
	  if (event.GUIEvent.EventType == gui::EGET_BUTTON_CLICKED )
	    chooseMenu(M_MAIN);
    	  break;
        case 10:
	  if (event.GUIEvent.EventType == gui::EGET_BUTTON_CLICKED )
	    {
	      _device->closeDevice();
	      _start = true;
	      _secondPlayer = false;
	    }
	  break;
          case 11:
  	  if (event.GUIEvent.EventType == gui::EGET_BUTTON_CLICKED )
	    {
	      _device->closeDevice();
	      _start = true;
	      _secondPlayer = true;
	    }
      	  break;
	}
    }
  if (isKeyPressed(irr::KEY_KEY_P, event))
    {
      _device->closeDevice();
      _start = true;
    }
  return false;
}
