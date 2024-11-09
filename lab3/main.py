#!/usr/bin/env python3

import pygame as pg
import pygame.freetype
import os
from enemy import Enemy
from player import Player
from projectile import Projectile
from pygame.locals import *

def main():
    # Startup pygame
    pg.init()

    # Get a screen object
    screen = pg.display.set_mode([1024, 768])
    
    # Create a player - TODO
    player = Player()

    # Create enemy and projectile Groups - TODO
    enemies = pg.sprite.Group()
    projectiles = pg.sprite.Group()

    switchEnemyType = 1

    for i in range(600, 1000, 75):
        for j in range(100, 600, 50):
            enemy = Enemy((i, j), switchEnemyType)
            enemies.add(enemy)

    # Start sound - Load background music and start it
    # playing on a loop - TODO
    pg.mixer.init()
    pg.mixer.music.load("assets/cpu-talk.mp3")
    pg.mixer.music.play(loops=-1, start=0.0)

    # Get font setup
    pg.freetype.init()
    font_path = os.path.join(os.path.dirname(os.path.realpath(__file__)), "./assets", "PermanentMarker-Regular.ttf")
    font_size = 64
    font = pg.freetype.Font(font_path, font_size)
    # Make a tuple for FONTCOLOR - TODO
    FONTCOLOR = (255, 255, 255)
    # Startup the main game loop
    running = True
    # Keep track of time
    delta = 0
    # Make sure we can't fire more than once every 250ms
    shotDelta = 250
    # Frame limiting
    fps = 60
    clock = pg.time.Clock()
    clock.tick(fps)
    # Setup score variable
    score = 0

    # Other game variables
    playerLives = 2
    play_round_one_only = 0

    while running:

        # First thing we need to clear the events.
        for event in pg.event.get():
            if event.type == pg.QUIT:
                running = False
            if event.type == pg.USEREVENT + 1:
                if switchEnemyType == 1:
                    score += 100
                elif switchEnemyType == 2:
                    score += 150
                elif switchEnemyType == 3:
                    score += 200
                elif switchEnemyType == 4:
                    score += 250
                elif switchEnemyType == 5:
                    score += 300

        keys = pg.key.get_pressed()

        if keys[K_s]:
            player.down(delta)
        if keys[K_w]:
            player.up(delta)
        if keys[K_a]:
            player.left(delta)
        if keys[K_d]:
            player.right(delta)
        if keys[K_q]:
            running = False
        if keys[K_SPACE]:
            if shotDelta >= .25:
                projectile = Projectile(player.rect, enemies)
                projectiles.add(projectile)
                shotDelta = 0
        if keys[K_1]:
                play_round_one_only = 1

        # Check if all enemies are cleared
        enemyCount = len(enemies)
        if enemyCount == 0:
            switchEnemyType += 1

            if switchEnemyType == 6 or play_round_one_only == 1:
                font.render_to(screen, (150, 150), "YOU WIN!", FONTCOLOR, None, size=165)
                pg.display.flip()
                pg.time.wait(2000)
                running = False

            for i in range(600, 1000, 75):
                for j in range(100, 600, 50):
                    enemy = Enemy((i, j), switchEnemyType)
                    enemies.add(enemy)

        # Ok, events are handled, let's update objects!
        player.update(delta)
        for enemy in enemies:
            enemy.update(delta)
        for projectile in projectiles:
            projectile.update(delta)

        # Objects are updated, now let's draw!
        screen.fill((0, 0, 0))
        player.draw(screen)
        enemies.draw(screen)
        projectiles.draw(screen)

        # Check for collision logic
        if pg.sprite.spritecollideany(player, enemies):
            if playerLives == 0:
                font.render_to(screen, (150, 150), "YOU LOSE", FONTCOLOR, None, size=165)
                pg.display.flip()
                pg.time.wait(2000)
                running = False

            playerLives -= 1
            player = Player()

        else:
            font.render_to(screen, (20, 20), "Score: " + str(score), FONTCOLOR, None, size=50)
            font.render_to(screen, (430, 20), "Lives: " + str(playerLives), FONTCOLOR, None, size=40)
            font.render_to(screen, (680, 20), "Press q to quit", FONTCOLOR, None, size=40)

            if play_round_one_only == 0:
                font.render_to(screen, (20, 680), "Press [ 1 ] to only play round 1", FONTCOLOR, None, size=40)
            else:
                font.render_to(screen, (20, 680), "Round 1 only", FONTCOLOR, None, size=40)

        # When drawing is done, flip the buffer.
        pg.display.flip()

        # How much time has passed this loop?
        delta = clock.tick(fps) / 1000.0
        shotDelta += delta

# Startup the main method to get things going.
if __name__ == "__main__":
    main()
    pg.quit()
