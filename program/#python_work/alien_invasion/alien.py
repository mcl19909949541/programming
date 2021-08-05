import pygame
from pygame.sprite import Sprite
class Alien(Sprite):
   #Class representing a single alien
   def __init__(self,ai_settings,screen):
      
       #Initialize the alien and set its starting position
        super(Alien,self).__init__()
        self.screen = screen
        self.ai_settings = ai_settings
       
       #Load the alien image and set its rect property
        self.image = pygame.image.load('images/alien.bmp')
        self.rect = self.image.get_rect()
        
        #Each alien is initially near the top left corner of the screen
        self.rect.x = self.rect.width
        self.rect.y = self.rect.height
        
        #Store the exact location of the alien
        self.x=float(self.rect.x)
        
   def blitme(self):
        #Draw an alien at a specified location
        self.screen.blit(self.image,self.rect)
    
   def update(self):
        self.x += (self.ai_settings.alien_speed_factor * self.ai_settings.fleet_direction)
        self.rect.x = self.x
    
   def check_edges(self):
       screen_rect = self.screen.get_rect()
       if self.rect.right >=screen_rect.right:
           return True
       elif self.rect.left <= 0:
           return True
        
        
