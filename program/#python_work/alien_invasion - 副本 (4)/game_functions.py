import sys
import pygame
from bullet import Bullet
from alien import Alien
from time import sleep

def check_keydown_events(event,ai_settings,screen,ship,bullets):
   
    #Response button
    if event.key == pygame.K_RIGHT:
                    ship.moving_right = True
                       
    elif event.key == pygame.K_LEFT:
                    ship.moving_left =True
    elif event.key == pygame.K_SPACE:
     fire_bullet(ai_settings, screen, ship, bullets)
    elif event.key  == pygame.K_q:
        sys.exit()

def check_keyup_events(event,ship):
    
    #Response release
    if event.key == pygame.K_RIGHT:
                    ship.moving_right =False    
    elif event.key == pygame.K_LEFT:
                    ship.moving_left = False
def check_events(ai_settings, screen, stats,sb, play_button, ship, aliens,bullets):
    
    
    #Response to button and mouse events
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            sys.exit()
        elif event.type==pygame.KEYDOWN:
            check_keydown_events(event, ai_settings, screen, ship, bullets)
                       
        
        elif event.type == pygame.KEYUP:
            check_keyup_events(event, ship)
        elif event.type == pygame.MOUSEBUTTONDOWN:
            mouse_x, mouse_y = pygame.mouse.get_pos()
            check_play_button(ai_settings, screen, stats,sb, play_button, ship,aliens, bullets, mouse_x, mouse_y)
            
def check_play_button(ai_settings, screen, stats,sb, play_button, ship, aliens,bullets, mouse_x, mouse_y):
    
    button_clicked = play_button.rect.collidepoint(mouse_x, mouse_y)
    if button_clicked and not stats.game_active:
        pygame.mouse.set_visible(False)
        ai_settings.initialize_dynamic_settings()
        stats.reset_stats()
        stats.game_active = True
        
        aliens.empty()
        bullets.empty()
        
        sb.prep_score()
        sb.prep_high_score()
        sb.prep_level()
        sb.prep_ships()
        
        create_fleet(ai_settings, screen, ship, aliens)
        ship.center_ship()

def update_screen(ai_settings, screen, stats, sb,ship, aliens, bullets,play_button):
    
    sb.show_score()
    if not stats.game_active:
        play_button.draw_button()
    pygame.display.flip()
    screen.fill(ai_settings.bg_color)
    for bullet in bullets.sprites():
        bullet.draw_bullet()
    ship.blitme()
    aliens.draw(screen)
    
    #Make the recently drawn screen visible
    pygame.display.flip()
    
def update_bullets(ai_settings,screen,stats,sb,ship,aliens,bullets):
    
    #Update the location of the bullets and delete those that have disappeared
    
    #Update bullet location
    bullets.update()
    
    #Delete lost bullets
    for bullet in bullets.copy():
        if bullet.rect.bottom <= 0:
            bullets.remove(bullet)
            
    check_bullet_alien_collisions(ai_settings, screen,stats,sb, ship, aliens, bullets)

def check_bullet_alien_collisions(ai_settings, screen,stats,sb, ship, aliens, bullets):
   #Check to see if a bullet hit the alien
    #If so, delete the corresponding bullets and aliens
    collisions = pygame.sprite.groupcollide(bullets,aliens,True,True)
    if collisions:
       for aliens in collisions.values():
            stats.score += ai_settings.alien_points
            sb.prep_score()
       check_high_score(stats, sb)
        
    if len(aliens) == 0:
        bullets.empty()
        ai_settings.increase_speed()
        create_fleet(ai_settings, screen, ship, aliens)
        stats.level += 1
        sb.prep_level()
        
    print(len(bullets))
    
     
def fire_bullet(ai_settings, screen, ship, bullets):
    
    #Create a bullet and add it to the group bullets
     if len(bullets)<ai_settings.bullets_allowed:
                     new_bullet = Bullet(ai_settings, screen, ship) 
                     bullets.add(new_bullet) 

def create_fleet(ai_settings,screen,ship,aliens):
    #create aliens group
    alien=Alien(ai_settings,screen)
    number_aliens_x = get_number_aliens_x(ai_settings, alien.rect.width)
    number_rows = get_number_rows(ai_settings, ship.rect.height,
    alien.rect.height)
    
    #create aliens for first line
    for row_number in range(number_rows): 
       for alien_number in range(number_aliens_x):
            create_alien(ai_settings, screen, aliens, alien_number,
            row_number)

def get_number_aliens_x(ai_settings, alien_width):
    available_space_x = ai_settings.screen_width - 2 * alien_width
    number_aliens_x = int(available_space_x / (2 * alien_width))
    return number_aliens_x

def create_alien(ai_settings, screen, aliens, alien_number,row_number):
    alien = Alien(ai_settings, screen)
    alien_width = alien.rect.width
    alien.x = alien_width + 2 * alien_width * alien_number
    alien.rect.x = alien.x
    alien.rect.y = alien.rect.height + 2 * alien.rect.height * row_number
    aliens.add(alien)

def get_number_rows(ai_settings,ship_height,alien_height):
    
    #How many lines can the screen hold
    available_space_y = (ai_settings.screen_height-(3*alien_height) -
    ship_height)
    number_rows = int(available_space_y / (2 * alien_height))
    return number_rows
    
def check_fleet_edges(ai_settings, aliens):
    #Take corresponding measures when aliens arrive at the edge
    for alien in aliens.sprites():
        if alien.check_edges():
           change_fleet_direction(ai_settings, aliens)
           break   

def change_fleet_direction(ai_settings, aliens):
    #Move the whole group down and change their direction
    
    ai_settings.fleet_direction *= -1
    for alien in aliens.sprites():
        alien.rect.y += ai_settings.fleet_drop_speed 
   
def update_aliens(ai_settings, stats, sb,screen, ship, aliens, bullets):
   
    #Update the location of all aliens in the alien population
    check_fleet_edges(ai_settings, aliens)
    aliens.update()
    
    #Check for aliens at the bottom of the screen
    check_aliens_bottom(ai_settings, screen, stats, sb, ship, aliens, bullets)
    
    #Detecting collisions between aliens and spaceships
    if pygame.sprite.spritecollideany(ship,aliens):
        print("Y SUCK!!!")
        ship_hit(ai_settings,stats,sb,screen,ship,aliens,bullets)
        

def ship_hit(ai_settings,stats,sb,screen,ship,aliens,bullets):
    if stats.ships_left > 0:
        stats.ships_left -= 1
        
        aliens.empty()
        bullets.empty()
        
        create_fleet(ai_settings, screen,sb, ship, aliens)
        ship.center_ship()
        sb.prep_ships()
        
        sleep(0.5)
        
    else:
        stats.game_active = False
        pygame.mouse.set_visible(True)

def check_aliens_bottom(ai_settings, stats, screen, sb, ship, aliens,bullets):
    screen_rect = screen.get_rect()
    for alien in aliens.sprites():
       if alien.rect.bottom >= screen_rect.bottom:
         ship_hit(ai_settings,stats,sb,screen,ship,aliens,bullets)
         break   

def check_high_score(stats, sb):
    if stats.score > stats.high_score:
       stats.high_score = stats.score
       sb.prep_high_score()

