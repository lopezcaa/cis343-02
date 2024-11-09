import os
import pygame as pg

class Enemy(pg.sprite.Sprite):
    def __init__(self, position, ship):
        super(Enemy, self).__init__()

        if ship == 1:
            enemy_image = pg.image.load(os.path.join('assets', 'Ship1.png')).convert_alpha()
            self.speed = 1
        elif ship == 2:
            enemy_image = pg.image.load(os.path.join('assets', 'Ship2.png')).convert_alpha()
            self.speed = 2
        elif ship == 3:
            enemy_image = pg.image.load(os.path.join('assets', 'Ship3.png')).convert_alpha()
            self.speed = 3
        elif ship == 4:
            enemy_image = pg.image.load(os.path.join('assets', 'Ship4.png')).convert_alpha()
            self.speed = 4
        elif ship == 5:
            enemy_image = pg.image.load(os.path.join('assets', 'Ship5.png')).convert_alpha()
            self.speed = 5

        flippedImage = pg.transform.flip(enemy_image, flip_x=True, flip_y=False)
        self.image = flippedImage

        self.rect = self.image.get_rect()
        self.rect.topleft = position

    def update(self, delta):
        self.rect.x -= self.speed
        
        # Logic to make the enemies move up and down
        # Based off of forward pixel movement
        holding = int(self.rect.x % 150)
        if (0 <= holding < 75) % 2 == 0:
            if holding % 3 == 0:
                self.rect.y += 1
        elif (75 <= holding <= 150) % 2 == 0:
            if holding % 3 == 0:
                self.rect.y -= 1

        # Reset the enemy when it goes off-screen to the left
        if self.rect.x <= 0:
            self.rect.x = 1024
