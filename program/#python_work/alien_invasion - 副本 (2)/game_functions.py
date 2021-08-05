import sys
import pygame
from bullet import Bullet
def check_keydown_events(event,ai_settings,screen,ship,bullets):
    #Response button
    if event.key == pygame.K_RIGHT:
                    ship.moving_right = True
                       
    elif event.key == pygame.K_LEFT:
                    ship.moving_left =True
    elif event.key == pygame.K_SPACE:
     fire_bullet(ai_settings, screen, ship, bullets)

def check_keyup_events(event,ship):
    #Response release
    if event.key == pygame.K_RIGHT:
                    ship.moving_right =False    
    elif event.key == pygame.K_LEFT:
                    ship.moving_left = False
def check_events(ai_settings,screen,ship,bullets):
    
    #Response to button and mouse events
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            sys.exit()
        elif event.type==pygame.KEYDOWN:
            check_keydown_events(event, ai_settings, screen, ship, bullets)
                       
        
        elif event.type == pygame.KEYUP:
            check_keyup_events(event, ship)
                        
def update_screen(ai_settings,screen,ship,bullets):
    #Update the image on the screen and switch to the new screen
    
    #Redraw the screen every time you cycle
    screen.fill(ai_settings.bg_color)
    for bullet in bullets.sprites():
        bullet.draw_bullet()
    ship.blitme()
    
    #Make the recently drawn screen visible
    pygame.display.flip()
    
def update_bullets(bullets):
    #Update the location of the bullets and delete those that have disappeared
    
    #Update bullet location
    bullets.update()
    
    #Delete lost bullets
    for bullet in bullets.copy():
        if bullet.rect.bottom <= 0:
            bullets.remove(bullet)
    #print(len(bullets))

def fire_bullet(ai_settings, screen, ship, bullets):
    #Create a bullet and add it to the group bullets
     if len(bullets)<ai_settings.bullets_allowed:
                     new_bullet = Bullet(ai_settings, screen, ship) 
                     bullets.add(new_bullet) 
