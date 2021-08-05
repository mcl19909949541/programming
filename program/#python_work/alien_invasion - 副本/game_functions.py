import sys
import pygame
def check_keydown_events(event,ship):
    #Response button
    if event.key == pygame.K_RIGHT:
                    ship.moving_right = True
                       
    elif event.key == pygame.K_LEFT:
                    ship.moving_left =True

def check_keyup_events(event,ship):
    #Response release
    if event.key == pygame.K_RIGHT:
                    ship.moving_right =False    
    elif event.key == pygame.K_LEFT:
                    ship.moving_left = False
def check_events(ship):
    
    #Response to button and mouse events
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            sys.exit()
        elif event.type==pygame.KEYDOWN:
            check_keydown_events(event,ship)
                       
        
        elif event.type == pygame.KEYUP:
            check_keyup_events(event, ship)
                        
def update_screen(ai_settings,screen,ship):
    #Update the image on the screen and switch to the new screen
    
    #Redraw the screen every time you cycle
    screen.fill(ai_settings.bg_color)
    ship.blitme()
    
    #Make the recently drawn screen visible
    pygame.display.flip()
    
    
