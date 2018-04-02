set_size(640, 480)

clear()

look_at(4, 1, 2, 0, 0, -1, 0, 1, 0)
set_perspective(45, 1.33, 0.2, 4.5)

sphere_g = Geometry.sphere(0, -1000, -1, 999.5)
material_g = Material.lambertian(0.5, 0.5, 0.5)
object_g = Object.new(sphere_g, material_g)
add_object(object_g)

sphere_w = Geometry.sphere(0, -1000, -1, 999.8)
material_w = Material.dielectric(1.33)
object_w = Object.new(sphere_w, material_w)
add_object(object_w)

sphere_a = Geometry.sphere(-1.6, 0, -1, 0.5)
material_a = Material.lambertian(0.5, 0.5, 0.9)
object_a = Object.new(sphere_a, material_a)
add_object(object_a)

sphere_b = Geometry.sphere(0.0, 0.0, -1, 0.5)
material_b = Material.metal(0.85, 0.64, 0.12, 0.5)
object_b = Object.new(sphere_b, material_b)
add_object(object_b)

sphere_c = Geometry.sphere(1.6, 0.0, -1, 0.5)
material_c = Material.metal(0.7, 0.7, 0.7, 0.8)
object_c = Object.new(sphere_c, material_c)
add_object(object_c)

sphere_d = Geometry.sphere(-1.2, 0.0, 0.5, 0.5)
material_d = Material.metal(0.9, 0.9, 0.9, 0.0)
object_d = Object.new(sphere_d, material_d)
add_object(object_d)

render("sample.jpg")
