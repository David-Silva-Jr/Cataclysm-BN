#include "catalua_bindings.h"

#include "catalua_bindings_utils.h"
#include "catalua_luna.h"
#include "catalua_luna_doc.h"

#include "faction.h"

void reg_faction( sol::state &lua )
{
    #define UT_CLASS faction
    {
        sol::usertype<faction> ut = luna::new_usertype<faction>( lua, luna::no_bases, luna::no_constructor );

        DOC( "Name of the faction." );
        SET_FX( name );
        DOC( "How much the faction likes you." );
        SET_FX( likes_u );
        DOC( "How much the faction respects you." );
        SET_FX( respects_u );
        DOC( "Do you know about this faction?" );
        SET_FX( known_by_u );
        DOC( "ID of the faction." );
        SET_FX( id );
        DOC( "Raw description of the faction." );
        SET_FX( desc );
        DOC( "How big is the sphere of influence of the faction?" );
        SET_FX( size );
        DOC( "How powerful is the faction?" );
        SET_FX( power );
        DOC( "Nutritional value held by faction." );
        SET_FX( food_supply );
        DOC( "Total wealth of the faction." );
        SET_FX( wealth );
        DOC( "Is this a faction for just one person?" );
        SET_FX( lone_wolf_faction );
        DOC( "ID of the faction currency." );
        SET_FX( currency );
        DOC( "What a person have with the faction?" );
        SET_FX( relations );
        DOC( "mon_faction_id of the monster faction; defaults to human." );
        SET_FX( mon_faction );
        DOC( "Epilogue strings." );
        SET_FX( epilogue_data );

        DOC( "Getter for desc." );
        SET_FX( describe );
        DOC( "Get faction epilogues." );
        SET_FX( epilogue );
        DOC( "Get a description of the faction's food supply." );
        SET_FX( food_supply_text );
        DOC( "Get the color of the food supply text." );
        SET_FX( food_supply_color );

        DOC( "Does the person have a given relation with a faction?" );
        luna::set_fx( ut, "has_relationship", [](
            faction &fac,
            faction_id guy_id,
            npc_factions::relationship flag
        ) { return fac.has_relationship(guy_id, flag); } );

        DOC( "Add person to faction. Bool is whether or not the player knows them." );
        luna::set_fx( ut, "add_to_membership", [](
            faction &fac,
            character_id guy_id,
            std::string guy_name,
            bool known
        ) { return fac.add_to_membership( guy_id, guy_name, known ); } );

        DOC( "Removes a person from the faction." );
        luna::set_fx( ut, "remove_member", [](
            faction &fac,
            character_id guy_id
        ) { return fac.remove_member( guy_id ); } );

        DOC( "Unused as far as I can tell. Can be reworked to store inter-faction relations?" );
        SET_FX( opinion_of );
        DOC( "Did the faction validate properly?" );
        SET_FX( validated );
        DOC( "List of faction members." );
        SET_FX( members );
    }
    #undef UT_CLASS
}

void reg_faction_manager( sol::state &lua )
{
    #define UT_CLASS faction_manager
    {
        sol::usertype<faction_manager> ut = luna::new_usertype<faction_manager>( lua, luna::no_bases, luna::no_constructor );

        DOC( "Deletes all factions." );
        SET_FX( clear );
        DOC( "Creates factions if none exist." );
        SET_FX( create_if_needed );
        DOC( "Displays faction menu (I think)" );
        SET_FX( display );

        DOC( "Creates a new faction based on a faction template." );
        luna::set_fx( ut, "add_new_faction", [](
            faction_manager &fac_manager,
            std::string name_new,
            faction_id id_new,
            faction_id template_id
        ) { return fac_manager.add_new_faction( name_new, id_new, template_id ); } );

        DOC( "Deletes a given faction." );
        luna::set_fx( ut, "remove_faction", [](
            faction_manager &fac_manager,
            faction_id id
        ) { return fac_manager.remove_faction( id ); } );


        DOC( "Returns a list of factions." );
        SET_FX( all );

        DOC( "Gets a faction by id." );
        luna::set_fx( ut, "get", [](
            faction_manager &fac_manager,
            faction_id id,
            bool complain
        ){ return fac_manager.get(id, complain); } );
    }
    #undef UT_CLASS
}