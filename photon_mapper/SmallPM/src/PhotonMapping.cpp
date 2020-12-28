/*********************************************************************************
Copyright (C) 2014 Adrian Jarabo (ajarabo@unizar.es)
Copyright (C) 2014 Diego Gutierrez (diegog@unizar.es)
All rights reserved.

This is an educational Ray Tracer developed for the course 'Informatica Grafica'
(Computer Graphics) tought at Universidad de Zaragoza (Spain). As such, it does not 
intend to be fast or general, but just to provide an educational tool for undergraduate
students. 

This software is provided as is, and any express or implied warranties are disclaimed.
In no event shall copyright holders be liable for any damage.
**********************************************************************************/
#include "PhotonMapping.h"
#include "World.h"
#include "Intersection.h"
#include "Ray.h"
#include "BSDF.h"
#include "BVH.h"

#include "Random.h"

#include <ostream>

vector<Real> vector3_to_vector(const Vector3 &v)
{
    return vector<Real>{v.getComponent(0), v.getComponent(1), v.getComponent(2)};
}

inline std::ostream &operator<<(std::ostream &os, const Vector3 &v)
{
    os << "[ " << v.getComponent(0) << ", " << v.getComponent(1) << ", " << v.getComponent(2) << " ]";
    return os;
}

#define EPSILON 0.01f

bool similar(Real a, Real b)
{
    return fabs(a - b) <= EPSILON;
}

bool similar(Vector3 a, Vector3 b)
{
    return similar(a.getComponent(0), b.getComponent(0)) && similar(a.getComponent(1), b.getComponent(1)) && similar(a.getComponent(2), b.getComponent(2));
}

//*********************************************************************
// Compute the photons by tracing the Ray 'r' from the light source
// through the scene, and by storing the intersections with matter
// in the lists 'xx_photons', storing the diffuse (global) and caustic
// photons respectively. For efficiency, both are computed at the same
// time, since computing them separately would result into a lost of
// several samples marked as caustic or diffuse.
// Same goes with the boolean 'direct', that specifies if direct
// photons (from light to surface) are being stored or not.
// The initial traced photon has energy defined by the tristimulus
// 'p', that accounts for the emitted power of the light source.
// The function will return true when there are more photons (caustic
// or diffuse) to be shot, and false otherwise.
//---------------------------------------------------------------------
bool PhotonMapping::trace_ray(const Ray &r, const Vector3 &p,
                              std::list<Photon> &global_photons, std::list<Photon> &caustic_photons, bool direct)
{

    //Check if max number of shots done...
    if (++m_nb_current_shots > m_max_nb_shots)
    {
        return false;
    }

    // Compute irradiance photon's energy
    Vector3 energy(p);

    Ray photon_ray(r);
    photon_ray.shift();

    bool is_caustic_particle = false;

    //Iterate the path
    while (1)
    {
        // Throw ray and update current_it
        Intersection it;
        world->first_intersection(photon_ray, it);

        if (!it.did_hit())
            break;

        //Check if has hit a delta material...
        if (it.intersected()->material()->is_delta())
        {
            // If delta material, then is caustic...
            // Don't store the photon!
            is_caustic_particle = true;
        }
        else if (photon_ray.get_level() > 0 || direct)
        {
            //If non-delta material, store the photon!
            if (is_caustic_particle)
            {
                //If caustic particle, store in caustics
                if (caustic_photons.size() < m_nb_caustic_photons)
                    caustic_photons.push_back(Photon(it.get_position(), photon_ray.get_direction(), energy));
            }
            else
            {
                //If non-caustic particle, store in global
                if (global_photons.size() < m_nb_global_photons)
                    global_photons.push_back(Photon(it.get_position(), photon_ray.get_direction(), energy));
            }
            is_caustic_particle = false;
        }

        Real pdf;

        Vector3 surf_albedo = it.intersected()->material()->get_albedo(it);
        Real avg_surf_albedo = surf_albedo.avg();

        Real epsilon2 = static_cast<Real>(rand()) / static_cast<Real>(RAND_MAX);
        while (epsilon2 < 0.)
            epsilon2 = static_cast<Real>(rand()) / static_cast<Real>(RAND_MAX);

        if (epsilon2 > avg_surf_albedo || photon_ray.get_level() > 20)
            break;

        // Random walk's next step
        // Get sampled direction plus pdf, and update attenuation
        it.intersected()->material()->get_outgoing_sample_ray(it, photon_ray, pdf);

        // Shade...
        energy = energy * surf_albedo;
        if (!it.intersected()->material()->is_delta())
            energy *= dot_abs(it.get_normal(), photon_ray.get_direction()) / 3.14159;

        energy = energy / (pdf * avg_surf_albedo);
    }

    if (caustic_photons.size() == m_nb_caustic_photons &&
        global_photons.size() == m_nb_global_photons)
    {
        m_max_nb_shots = m_nb_current_shots - 1;
        return false;
    }

    return true;
}

//*********************************************************************
// TODO: Implement the preprocess step of photon mapping,
// where the photons are traced through the scene. To do it,
// you need to follow these steps for each shoot:
//  1 - Sample a world's light source in the scene to create
//		the initial direct photon from the light source.
//	2 - Trace the photon through the scene storing the inter-
//		sections between the photons and matter. You can use
//		the function 'trace_ray' for this purpose.
//	3 - Finally, once all the photons have been shot, you'll
//		need to build the photon maps, that will be used later
//		for rendering.
//		NOTE: Careful with function
//---------------------------------------------------------------------
void PhotonMapping::preprocess()
{

    std::cout << "holaasdkfjalkdfjñalkdjfñaksdjfñ kasjdñfklasd" << std::endl;
    std::cout << "holaasdkfjalkdfjñalkdjfñaksdjfñ kasjdñfklasd" << std::endl;
    if (dynamic_cast<BVH *>(world->object_list[1]) == nullptr)
    {
        std::cout << "no es" << std::endl;
    }
    else
    {
        std::cout << "es" << std::endl;
    }
    world->light_source_list
        exit(1);

    // Stores true if there are more photons to be shot

    std::list<Photon> global_photons = {};
    std::list<Photon> caustic_photons = {};

    const LightSource *ls;
    Vector3 dir;

    // Número de fotones por fuente de luz
    // No se si hace falta hacer la división de debajo
    int num_photons = m_max_nb_shots / world->nb_lights();

    do
    {
        // Chose a random light source
        int idx = random_int(world->nb_lights() - 1);
        ls = &world->light(idx);

        // Sample a random point on the unit sphere
        dir = uniform_sphere_sample();

        // Shot photons while there are photons to be shot
    } while (trace_ray(Ray(ls->get_position(), dir), 4 * M_PI * ls->get_intensities() / num_photons, global_photons, caustic_photons, !m_raytraced_direct));

    // Creo que get intesities si que hay que dividirlo, porque esta es la energía total de la fuente de luz,
    // luego cada fotón tendrá una posción de esa energía.
    // Pero no se si este cálculo bien

    std::cout << global_photons.size() << std::endl;

    // Store the photons in the kd-trees
    m_global_map.clear();
    m_caustics_map.clear();

    if (global_photons.size() > 0)
    {
        for (Photon photon : global_photons)
        {
            m_global_map.store(vector3_to_vector(photon.position), photon);
        }
        m_global_map.balance();
    }

    if (caustic_photons.size() > 0)
    {
        for (Photon photon : caustic_photons)
        {
            m_caustics_map.store(vector3_to_vector(photon.position), photon);
        }
        m_caustics_map.balance();
    }

    std::cout << m_global_map.nb_elements() << std::endl;
    std::cout << m_caustics_map.nb_elements() << std::endl;
}

//*********************************************************************
// TODO: Implement the function that computes the rendering equation
// using radiance estimation with photon mapping, using the photon
// maps computed as a proprocess. Note that you will need to handle
// both direct and global illumination, together with recursive the
// recursive evaluation of delta materials. For an optimal implemen-
// tation you should be able to do it iteratively.
// In principle, the class is prepared to perform radiance estimation
// using k-nearest neighbors ('m_nb_photons') to define the bandwidth
// of the kernel.
//---------------------------------------------------------------------
Vector3 PhotonMapping::shade(Intersection &it0) const
{
    Vector3 L(0);
    Intersection it(it0);

    // Ray reflected_ray(it.get_ray());
    // reflected_ray.shift();
    Ray reflected_ray;

    Vector3 W(1);
    // Antes de llamar a shade se comprueba it.did_hit()

    int iteraciones = 0;
    // Si el material es delta, hay que ir siguiendo un camino hasta llegar a un material difuso
    while (it.intersected()->material()->is_delta() && iteraciones < 20)
    {
        // La pdf no se usa en materiales delta
        Real pdf; // Not used
        it.intersected()->material()->get_outgoing_sample_ray(it, reflected_ray, pdf);

        if (!it.did_hit())
        {
            return L;
        }

        // std::cout << it.intersected()->material()->get_albedo(it) << std::endl;

        // El albedo de los especulares y los transmisores es siempre 1 tal y como está
        // hecho todo, así que esto no haría falta.
        W = W * it.intersected()->material()->get_albedo(it);

        reflected_ray.shift();
        world->first_intersection(reflected_ray, it);

        // Pensar cuantas repeticiones máximo se puede hacer de esto

        // Ruleta rusa para salir de bucle
        // Esto se podría poner mejor, para que se haga igual que en trace_ray (límite de 20 y no se que)
        // float rand = random_real();
        // std::cout << rand << std::endl;
        // std::cout << reflected_ray.get_level() << std::endl;
        // Vector3 surf_albedo = it.intersected()->material()->get_albedo(it);
        // Real avg_surf_albedo = surf_albedo.avg();

        // if (random_real() > avg_surf_albedo || reflected_ray.get_level() > 20 || iteraciones > 20)
        // {
        // 	// std::cout << "iteraciones " << iteraciones << " " << rand << std::endl;
        // 	break;
        // }
        iteraciones++;
    }

    if (!it.did_hit() || it.intersected()->material()->is_delta())
    {
        return L;
    }

    Vector3 it_position = it.get_position();
    Vector3 it_albedo = it.intersected()->material()->get_albedo(it);
    Vector3 it_normal = it.get_normal();

    if (m_raytraced_direct)
    {
        // Hay que calcular la iluminación directa con ray tracing
        // Hacer next event estimation.

        // Elegir una luz aleatoria y sumar su contribución
        // Supongo que esta función ya tiene en cuenta el caso de que la luz no sea visible, entonces devolverá 0
        const LightSource *ls = &world->light(random_int(world->nb_lights()));
        if (ls->is_visible(it_position))
        {
            // std::cout << "entrado" << std::endl;
            // albedo * (luz incidente) * (coseno entre la luz incidente y la normal de la intersección)
            // No se si hay que normalizar los vectores
            // Hay que negar la incoming direction
            L += it_albedo * ls->get_incoming_light(it_position) * dot(-ls->get_incoming_direction(it_position).normalize(), it_normal);
            // std::cout << L.getComponent(0) << " " << L.getComponent(1) << " " << L.getComponent(2) << std::endl;
        }
    }

    /// Estimación de radiancia con los mapas de fotones

    std::vector<const KDTree<Photon, 3>::Node *> global_nodes;
    std::vector<const KDTree<Photon, 3>::Node *> caustic_nodes;
    Real radius;

    // Ahora buscamos los m_nb_photons (k) más cercanos, para obtener el radio
    m_global_map.find(vector3_to_vector(it_position), m_nb_photons, global_nodes, radius);
    for (auto node : global_nodes)
    {
        // No se si también hay que tener en cuenta el coseno entre el fotón y la normal de la intersección
        // Aquí habrá que hacer un kernel más complicado
        L += it_albedo * node->data().flux / (M_PI * radius * radius);
    }

    m_caustics_map.find(vector3_to_vector(it_position), m_nb_photons, caustic_nodes, radius);
    for (auto node : caustic_nodes)
    {
        L += it_albedo * node->data().flux / (M_PI * radius * radius);
    }

    return W * L;

    //**********************************************************************
    // The following piece of code is included here for two reasons: first
    // it works as a 'hello world' code to check that everthing compiles
    // just fine, and second, to illustrate some of the functions that you
    // will need when doing the work. Goes without saying: remove the
    // pieces of code that you won't be using.
    //
    unsigned int debug_mode = 8;

    switch (debug_mode)
    {
    case 1:
        // ----------------------------------------------------------------
        // Display Albedo Only
        L = it.intersected()->material()->get_albedo(it);
        break;
    case 2:
        // ----------------------------------------------------------------
        // Display Normal Buffer
        L = it.get_normal();
        break;
    case 3:
        // ----------------------------------------------------------------
        // Display whether the material is specular (or refractive)
        L = Vector3(it.intersected()->material()->is_delta());
        break;

    case 4:
        // ----------------------------------------------------------------
        // Display incoming illumination from light(0)
        L = world->light(0).get_incoming_light(it.get_position());
        break;

    case 5:
        // ----------------------------------------------------------------
        // Display incoming direction from light(0)
        L = world->light(0).get_incoming_direction(it.get_position());
        break;

    case 6:
        // ----------------------------------------------------------------
        // Check Visibility from light(0)
        if (world->light(0).is_visible(it.get_position()))
            L = Vector3(1.);
        break;

    case 7:

    {
        std::vector<const KDTree<Photon, 3>::Node *> global_nodes;
        std::vector<const KDTree<Photon, 3>::Node *> caustic_nodes;
        Real radius;

        m_global_map.find(vector3_to_vector(it.get_position()), m_nb_photons, global_nodes, radius);
        for (auto node : global_nodes)
        {
            L += it.intersected()->material()->get_albedo(it) * node->data().flux / (M_PI * radius * radius);
        }

        m_caustics_map.find(vector3_to_vector(it.get_position()), m_nb_photons, caustic_nodes, radius);
        for (auto node : caustic_nodes)
        {
            L += it.intersected()->material()->get_albedo(it) * node->data().flux / (M_PI * radius * radius);
        }

        // std::cout << L.data[0] << " " << L.data[1] << " " << L.data[2] << std::endl;

        // std::cout << global_nodes.size() << std::endl;
        // std::cout << radius << std::endl;

        break;
    }

    case 8:
    {
        std::list<const KDTree<Photon, 3>::Node *> global_nodes;
        std::list<const KDTree<Photon, 3>::Node *> caustic_nodes;

        m_global_map.find(vector3_to_vector(it.get_position()), 0.2, &global_nodes);
        m_caustics_map.find(vector3_to_vector(it.get_position()), 0.2, &caustic_nodes);

        // std::cout << global_nodes.size() << std::endl;
        /// std::cout << caustic_nodes.size() << std::endl;

        for (auto node : global_nodes)
        {
            L += node->data().flux;
        }
        L = L / global_nodes.size();

        for (auto node : caustic_nodes)
        {
            L += node->data().flux;
        }
        L = L / caustic_nodes.size();

        break;
    }

    case 9:
    {
        Photon global_ph = m_global_map.find(vector3_to_vector(it.get_position())).data();

        if (similar(global_ph.position, it.get_position()))
        {
            L = Vector3(5, 5, 5);
        }

        // Photon caustic_ph = m_caustics_map.find(vector3_to_vector(it.get_position())).data();

        // if (similar(caustic_ph.position, it.get_position()))
        // {
        // 	L = Vector3(5, 2, 5);
        // }
    }
    }
    // End of exampled code
    //**********************************************************************

    return L;
}
