class GameStats():
    #Track game statistics
    def __init__(self,ai_settings):
        #Initialization statistics
        self.ai_settings = ai_settings
        self.reset_stats()
        self.game_active = False
    def reset_stats(self):
        #Initializes statistics that may change during the game
        self.ships_left = self.ai_settings.ship_limit
        
