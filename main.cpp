/**
* @title fc2kv-t
 * @file main.cpp
 * @author typedef
 */

/*
 * https://github.com/fantasy-cat/FC2T
 */
#include <fc2.hpp>

int main( )
{
    if ( const auto session = fc2::get_session(); session.protection != 2 )
    {
        std::puts( "[fc2kv-t] this is only for kernel protection" );
        return 1;
    }

    const auto fc2kvt_draw_filled = fc2::call< bool >( "fc2kvt_draw_filled", FC2_LUA_TYPE::FC2_LUA_TYPE_BOOLEAN );
    const auto fc2kvt_draw_text = fc2::call< bool >( "fc2kvt_draw_text", FC2_LUA_TYPE::FC2_LUA_TYPE_BOOLEAN );
    const auto fc2kvt_draw_lines = fc2::call< bool >( "fc2kvt_draw_lines", FC2_LUA_TYPE::FC2_LUA_TYPE_BOOLEAN );

    /**
     *  create an infinite loop
     *  we're going to constantly attempt to mimic drawing requests and push it to kernel
     */
    while ( true )
    {
        /**
         *  something went wrong. fc2 solution may have closed.
         *  which is not a bad thing. it simply means it's also time to close this project too.
         */
        if ( fc2::get_error() != FC2_TEAM_ERROR_NO_ERROR ) break;

        for ( const auto & [ text, dimensions, style ] : fc2::draw::get() )
        {
            switch ( style[ FC2_TEAM_DRAW_STYLE_TYPE ] )
            {
                case FC2_TEAM_DRAW_TYPE_BOX:
                {
                    fc2::draw::box(
                        dimensions[ FC2_TEAM_DRAW_DIMENSIONS_LEFT ],
                        dimensions[ FC2_TEAM_DRAW_DIMENSIONS_TOP ],
                        dimensions[ FC2_TEAM_DRAW_DIMENSIONS_RIGHT ],
                        dimensions[ FC2_TEAM_DRAW_DIMENSIONS_BOTTOM ],
                        style[ FC2_TEAM_DRAW_STYLE_RED ],
                        style[ FC2_TEAM_DRAW_STYLE_GREEN ],
                        style[ FC2_TEAM_DRAW_STYLE_BLUE ],
                        style[ FC2_TEAM_DRAW_STYLE_ALPHA ],
                        style[ FC2_TEAM_DRAW_STYLE_THICKNESS ]
                    );
                    break;
                }

                case FC2_TEAM_DRAW_TYPE_BOX_FILLED:
                {
                    if ( !fc2kvt_draw_filled ) break;

                    fc2::draw::box_filled(
                        dimensions[ FC2_TEAM_DRAW_DIMENSIONS_LEFT ],
                        dimensions[ FC2_TEAM_DRAW_DIMENSIONS_TOP ],
                        dimensions[ FC2_TEAM_DRAW_DIMENSIONS_RIGHT ],
                        dimensions[ FC2_TEAM_DRAW_DIMENSIONS_BOTTOM ],
                        style[ FC2_TEAM_DRAW_STYLE_RED ],
                        style[ FC2_TEAM_DRAW_STYLE_GREEN ],
                        style[ FC2_TEAM_DRAW_STYLE_BLUE ],
                        style[ FC2_TEAM_DRAW_STYLE_ALPHA ]
                    );
                    break;
                }

                case FC2_TEAM_DRAW_TYPE_LINE:
                {
                    if ( !fc2kvt_draw_lines ) break;

                    fc2::draw::line(
                        dimensions[ FC2_TEAM_DRAW_DIMENSIONS_LEFT ],
                        dimensions[ FC2_TEAM_DRAW_DIMENSIONS_TOP ],
                        dimensions[ FC2_TEAM_DRAW_DIMENSIONS_RIGHT ],
                        dimensions[ FC2_TEAM_DRAW_DIMENSIONS_BOTTOM ],
                        style[ FC2_TEAM_DRAW_STYLE_RED ],
                        style[ FC2_TEAM_DRAW_STYLE_GREEN ],
                        style[ FC2_TEAM_DRAW_STYLE_BLUE ],
                        style[ FC2_TEAM_DRAW_STYLE_ALPHA ],
                        style[ FC2_TEAM_DRAW_STYLE_THICKNESS ]
                    );
                    break;
                }

                case FC2_TEAM_DRAW_TYPE_TEXT:
                {
                    if ( !fc2kvt_draw_text ) break;

                    fc2::draw::text(
                        text,
                        style[ FC2_TEAM_DRAW_STYLE_FONT_SIZE ],
                        dimensions[ FC2_TEAM_DRAW_DIMENSIONS_LEFT ],
                        dimensions[ FC2_TEAM_DRAW_DIMENSIONS_TOP ],
                        style[ FC2_TEAM_DRAW_STYLE_RED ],
                        style[ FC2_TEAM_DRAW_STYLE_GREEN ],
                        style[ FC2_TEAM_DRAW_STYLE_BLUE ],
                        style[ FC2_TEAM_DRAW_STYLE_ALPHA ]
                    );
                    break;
                }

                case FC2_TEAM_DRAW_TYPE_CIRCLE: case FC2_TEAM_DRAW_TYPE_CIRCLE_FILLED:
                {
                    static bool circle_flag = []
                    {
                        std::puts( "[fc2kv-t] circle is not supported in fc2kv" );
                        return true;
                    }( );
                    break;
                }

                default: break;
            }
        }
    }
    return 0;
}
