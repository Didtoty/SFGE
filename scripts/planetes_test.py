from SFGE import *
import math

class PlanetesTest(Component):
    def init(self):
        self.body = self.game_object.get_component(Component.Body)

    def update(self, dt):
        current_pos = self.game_object.transform.get_position()
        r = p2Vec2(current_pos.x - 300, current_pos.y - 300)
        magnitude = math.sqrt(math.pow(r.x, 2) + math.pow(r.y, 2))
        n = p2Vec2(r.x / magnitude, r.y / magnitude)
        newVel = p2Vec2(-n.x * 50.0, n.y * 50.0) 
        newVel = p2Vec2(newVel.x * magnitude * magnitude, newVel.y * magnitude * magnitude)
        print("NewVel x : " + str(newVel.x) + " ; y:" + str(newVel.y))
        if self.body:
            self.body.velocity = newVel

    def on_trigger_enter(self, collider):
        pass

    def on_trigger_exit(self, collider):
        pass
