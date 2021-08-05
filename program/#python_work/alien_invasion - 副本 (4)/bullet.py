import pygame
from pygame.sprite import Sprite

class Bullet(Sprite):
    #A class that manages the bullets launched by a spaceship
    def __init__(self,ai_settings,screen,ship):
       
       #Create a bullet object where the ship is
       super(Bullet,self).__init__()
       self.screen = screen
       
       #Create a rectangle at (0,0) to represent the bullet, and then set the correct position
       self.rect = pygame.Rect(0,0,ai_settings.bullet_width,ai_settings.bullet_height)
       self.rect.centerx = ship.rect.centerx
       self.rect.top = ship.rect.top
       
       #Store bullet position in decima
       self.y=float(self.rect.y)
       
       self.color = ai_settings.bullet_color
       self.speed_factor = ai_settings.bullet_speed_factor
    
    def update(self):
        #Move the bullet up
        
        #Update the decimal value that represents the bullet position
        self.y-=self.speed_factor
        
        #Update the position of the rect that represents the bullet
        self.rect.y = self.y
        
    def draw_bullet(self):
        #Draw bullets on the screen
        pygame.draw.rect(self.screen,self.color,self.rect)
