import pygame
from settings import Settings
from ship import Ship
from pygame.sprite import Group
import game_functions as gf

def run_game():
	
		pygame.init()
		ai_settings=Settings()
		
		#setting backgroud
		screen=pygame.display.set_mode((ai_settings.screen_width,ai_settings.screen_height))
		pygame.display.set_caption("Alien Invasion")
		
		#Create a spaceship
		ship=Ship(ai_settings,screen)
		
		#Create a group to store bullets
		bullets = Group()
		
		#setting backgroud color
		bg_color=(230,230,230)
		
		
		
		while True:
			
			gf.check_events(ai_settings,screen,ship,bullets)
			ship.update()
			gf.update_bullets(bullets)
			gf.update_screen(ai_settings,screen,ship,bullets)
			
run_game()


