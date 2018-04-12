from SFGE import *
import math

class PlanetesTest(Component):
    def init(self):
        self.body = self.game_object.get_component(Component.Body)

    def update(self, dt):
        current_pos = self.game_object.transform.get_position()
        print("current_pos : " + str(current_pos.x) + ";" + str(current_pos.y))
        r = p2Vec2(300 - current_pos.x, 300 - current_pos.y)
        magnitude = math.sqrt(r.x**2 + r.y**2)
        #print("magnitude : " + str(magnitude))
        n = p2Vec2(r.x / magnitude, r.y / magnitude)
        newVel = p2Vec2(n.x * 500.0, n.y * 500.0) 
        newVel = p2Vec2(newVel.x / magnitude / magnitude, newVel.y / magnitude / magnitude)
        print("newVel : " + str(newVel.x) + ";" + str(newVel.y))
        print("oldVel : " + str(self.body.velocity.x) + ";" + str(self.body.velocity.y))
        if self.body:
            self.body.velocity = p2Vec2(self.body.velocity.x + newVel.x, self.body.velocity.y + newVel.y)

    def on_trigger_enter(self, collider):
        pass

    def on_trigger_exit(self, collider):
        pass
