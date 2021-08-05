import pygame
from settings import Settings
from ship import Ship
from alien import Alien
from pygame.sprite import Group
from game_stats import GameStats
from button import Button
import game_functions as gf

def run_game():
	
		pygame.init()
		ai_settings=Settings()
		
		#setting backgroud
		screen=pygame.display.set_mode((ai_settings.screen_width,ai_settings.screen_height))
		pygame.display.set_caption("Alien Invasion")
		
		#create "playing" button
		play_button = Button(ai_settings, screen, "DO NOT GG")
		
		#Create a spaceship
		ship=Ship(ai_settings,screen)
		
		#Create a group to store bullets and aliens
		ship = Ship(ai_settings,screen)
		bullets = Group()
		aliens = Group()
		
		#create aliens group
		gf.create_fleet(ai_settings,screen,ship,aliens)
		
		#setting backgroud color
		bg_color=(230,230,230)
		
		#Create  aliens
		alien = Alien(ai_settings,screen)
		
		#Create an instance to store game statistics
		stats = GameStats(ai_settings)
		
		
		
		while True:
			gf.check_events(ai_settings, screen, stats, play_button, ship,aliens,bullets)
			if stats.game_active:
				ship.update()
				gf.update_bullets(ai_settings, screen, ship, aliens, bullets)
				gf.update_aliens(ai_settings, stats, screen, ship, aliens, bullets)
			gf.update_screen(ai_settings, screen, stats, ship, aliens, bullets, play_button)
			
run_game()


