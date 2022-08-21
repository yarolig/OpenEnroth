#pragma once

#include "Engine/VectorTypes.h"

struct BLVFace;

struct CollisionState {
    /**
     * Original offset 0x0047050A.
     *
     * Prepares this struct by filling all necessary fields, and checks whether there is actually no movement.
     *
     * @param dt                        Time delta, in fixpoint seconds.
     * @return                          True if there is no movement, false otherwise.
     */
    bool PrepareAndCheckIfStationary(int dt_fp);

    // actor is modeled as two spheres, basically "feet" & "head". Collisions are then done for both spheres.

    bool check_hi;  // Check the hi sphere collisions. If not set, only the lo sphere is checked.
    float radius_lo;   // radius of the lo ("feet") sphere.
    float radius_hi;  // radius of the hi ("head") sphere.
    Vec3_float_ position_lo; // center of the lo sphere.
    Vec3_float_ position_hi; // center of the hi sphere.
    Vec3_float_ new_position_lo; // desired new position for the center of the lo sphere.
    Vec3_float_ new_position_hi; // desired new position for the center of the hi sphere.
    Vec3_float_ velocity;  // Movement vector.
    Vec3_float_ direction;  // Movement direction, basically velocity as a unit vector.
    float speed = 0;  // Velocity magnitude.
    float total_move_distance;  // Total move distance, accumulated between collision iterations, starts at 0.
    float move_distance;  // Desired movement distance for current iteration, minus the distance already covered.
    float adjusted_move_distance;  // Movement distance for current iteration, adjusted after collision checks.
    unsigned int uSectorID = 0;  // Indoor sector id.
    unsigned int pid;  // PID of the object that we're collided with.
    int ignored_face_id;  // Don't check collisions with this face.
    BBox_float_ bbox;
};

extern CollisionState collision_state;

/**
 * Original offset 0x46E44E.
 *
 * Performs collisions with level geometry in indoor levels. Updates `collision_state`.
 *
 * @param ignore_ethereal               Whether ethereal faces should be ignored by this function.
 */
void CollideIndoorWithGeometry(bool ignore_ethereal);

/**
 * Original offset 0x46E889.
 *
 * Performs collisions with models in outdoor levels. Updates `collision_state`.
 *
 * @param ignore_ethereal               Whether ethereal faces should be ignored by this function.
 */
void CollideOutdoorWithModels(bool ignore_ethereal);

/**
 * Original offset 0x46E0B2.
 */
void CollideIndoorWithDecorations();

/**
 * Original offset 0x46E26D.
 *
 * @param grid_x                        Grid x coordinate.
 * @param grid_y                        Grid y coordinate.
 */
void CollideOutdoorWithDecorations(int grid_x, int grid_y);

/**
 * Original offset 0x46F04E.
 *
 * Performs collision checks with portals. Updates `collision_state`. If the collision did happen, then
 * `adjusted_move_distance` member is set to `0xFFFFFF` (basically a large number).
 *
 * @return                              True if there were no collisions with portals.
 */
bool CollideIndoorWithPortals();

/**
 * Original offset 0x46DF1A.
 *
 * @param actor_idx                     Actor index.
 * @param override_radius               Override actor's radius. Pass zero to use original radius.
 * @return                              Whether the collision is possible.
 */
bool CollideWithActor(int actor_idx, int override_radius);


void _46ED8A_collide_against_sprite_objects(unsigned int _this);

/**
 * Original offset 0x46EF01.
 *
 * @param jagged_top                Makes collision happen even if the monster would end up above the party.
 *                                  However, for the collision to happen, corresponding bounding boxes still need to
 *                                  intersect.
 */
void CollideWithParty(bool jagged_top);

