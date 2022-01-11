/**
* decalqueue.h
*
* Copyright (C) 2001-2002 Daniel Horn
* Copyright (C) 2002-2019 pyramid3d and other Vega Strike Contributors
* Copyright (C) 2019-2022 Stephen G. Tuggy and other Vega Strike Contributors
*
* https://github.com/vegastrike/Vega-Strike-Engine-Source
*
* This file is part of Vega Strike.
*
* Vega Strike is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 2 of the License, or
* (at your option) any later version.
*
* Vega Strike is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with Vega Strike. If not, see <https://www.gnu.org/licenses/>.
*/

#include "vs_globals.h"
#include "gfx/aux_texture.h"

#include <vector>
#include <string>

/*
 * A decal is a plastic, cloth, paper, or ceramic substrate that has printed on it a pattern or image that
 * can be moved to another surface upon contact, usually with the aid of heat or water.
 *
 * The original code implemented its own ref counting. TODO:I replaced that with a singleton that holds all textures
 * until the game exits. This should be a reasonable implementation for almost all scenarios.
 */

using std::vector;

class DecalQueue
{
    vector< Texture* >decals;

public:
    inline Texture * GetTexture( const unsigned int reference )
    {
        return decals[reference];
    }

    unsigned int AddTexture( std::string const &texname, enum FILTER mipmap )
    {
        Texture *texture = Texture::Exists( texname );

        // Texture already exists
        if (texture) {
            // Check if DecalQueue has the decal in the vector.
            // If so, return the index.
            vector<Texture*>::iterator it = std::find(decals.begin(), decals.end(), texture);
            if(it != decals.end()) {
                return std::distance(decals.begin(), it);
            }

            // Decal not in queue. Add
            decals.push_back(texture);
            return decals.size()-1;
        }

        // Need to create texture
        texture = new Texture( texname.c_str(), 0, mipmap, TEXTURE2D, TEXTURE_2D, GFXTRUE );
        decals.push_back(texture);
        return decals.size()-1;
    }
};

