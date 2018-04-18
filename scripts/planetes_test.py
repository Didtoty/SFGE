from SFGE import *
import math

class PlanetesTest(Component):
    def init(self):
        self.body = self.game_object.get_component(Component.Body)

    def update(self, dt):
        massSun = 500.0
        posSun = [300, 300]
        current_pos = self.game_object.transform.get_position()
        current_mass = self.body.get_mass()
        r = p2Vec2(posSun[0] - current_pos.x, posSun[1] - current_pos.y)
        magnitude = math.sqrt(r.x**2 + r.y**2)
        gravitationForce = massSun * current_mass / magnitude / magnitude

        force = p2Vec2(r.x * gravitationForce, r.y * gravitationForce)
        
        if self.body:
            self.body.apply_force(force)

    def on_trigger_enter(self, collider):
        pass

    def on_trigger_exit(self, collider):
        pass
