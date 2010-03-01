/* -*-c++-*- */
/* osgEarth - Dynamic map generation toolkit for OpenSceneGraph
 * Copyright 2008-2009 Pelican Ventures, Inc.
 * http://osgearth.org
 *
 * osgEarth is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>
 */
#include <osgEarthFeatures/Query>

using namespace osgEarth::Features;

Query::Query( const Config& conf )
{
    fromConfig( conf );
}

void
Query::fromConfig( const Config& conf )
{
    if ( !conf.getIfSet( "expr", _expression ) )
        if ( !conf.getIfSet( "where", _expression ) )
            if ( !conf.getIfSet( "sql", _expression ) )
                conf.getIfSet( "expression", _expression );

    Config b = conf.child( "extent" );
    if( !b.empty() )
    {
        _bounds = Bounds(
            b.value<double>( "xmin", 0.0 ),
            b.value<double>( "ymin", 0.0 ),
            b.value<double>( "xmax", 0.0 ),
            b.value<double>( "ymax", 0.0 ) );
    }
}

Config
Query::toConfig() const
{
    Config conf( "query" );
    conf.addIfSet( "expr", _expression );
    if ( _bounds.isSet() ) {
        Config bc( "extent" );
        bc.add( "xmin", toString(_bounds->xMin()) );
        bc.add( "ymin", toString(_bounds->yMin()) );
        bc.add( "xmax", toString(_bounds->xMax()) );
        bc.add( "ymax", toString(_bounds->yMax()) );
        conf.add( bc );
    }
    return conf;
}


