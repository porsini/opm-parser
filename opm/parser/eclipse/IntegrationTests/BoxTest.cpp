/*
  Copyright 2013 Statoil ASA.

  This file is part of the Open Porous Media project (OPM).

  OPM is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  OPM is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with OPM.  If not, see <http://www.gnu.org/licenses/>.
 */

#define BOOST_TEST_MODULE BoxTest
#include <boost/test/unit_test.hpp>
#include <boost/test/test_tools.hpp>

#include <opm/parser/eclipse/Deck/Deck.hpp>
#include <opm/parser/eclipse/Parser/Parser.hpp>
#include <opm/parser/eclipse/EclipseState/EclipseState.hpp>


using namespace Opm;

// forward declaration to avoid a pedantic compiler warning
EclipseState makeState(const std::string& fileName);

EclipseState makeState(const std::string& fileName) {
    ParserPtr parser(new Parser( ));
    boost::filesystem::path boxFile(fileName);
    DeckPtr deck =  parser->parseFile(boxFile.string() , false);
    EclipseState state(deck);
    return state;
}



BOOST_AUTO_TEST_CASE( PARSE_BOX_OK ) {
    EclipseState state = makeState("testdata/integration_tests/BOX/BOXTEST1");
    std::shared_ptr<GridProperty<int> > satnum = state.getIntGridProperty("SATNUM");
    {
        size_t i,j,k;
        std::shared_ptr<const EclipseGrid> grid = state.getEclipseGrid();
        for (k = 0; k < grid->getNZ(); k++) {
            for (j = 0; j < grid->getNY(); j++) {
                for (i = 0; i < grid->getNX(); i++) {

                    size_t g = i + j*grid->getNX() + k * grid->getNX() * grid->getNY();
                    if (i <= 1 && j <= 1 && k <= 1)
                        BOOST_CHECK_EQUAL(satnum->iget(g) , 10);
                    else
                        BOOST_CHECK_EQUAL(satnum->iget(g) , 2);
                    
                }
            }
        }
    }
}



BOOST_AUTO_TEST_CASE( PARSE_MULTIPLY_COPY ) {
    EclipseState state = makeState("testdata/integration_tests/BOX/BOXTEST1");
    std::shared_ptr<GridProperty<int> > satnum = state.getIntGridProperty("SATNUM");
    std::shared_ptr<GridProperty<int> > fipnum = state.getIntGridProperty("FIPNUM");
    size_t i,j,k;
    std::shared_ptr<const EclipseGrid> grid = state.getEclipseGrid();
    
    for (k = 0; k < grid->getNZ(); k++) {
        for (j = 0; j < grid->getNY(); j++) {
            for (i = 0; i < grid->getNX(); i++) {
                
                size_t g = i + j*grid->getNX() + k * grid->getNX() * grid->getNY();
                if (i <= 1 && j <= 1 && k <= 1)
                    BOOST_CHECK_EQUAL(4*satnum->iget(g) , fipnum->iget(g));
                else
                    BOOST_CHECK_EQUAL(2*satnum->iget(i,j,k) , fipnum->iget(i,j,k));

            }
        }
    }
}


BOOST_AUTO_TEST_CASE( INCOMPLETE_KEYWORD_BOX) {
    BOOST_CHECK_THROW( makeState("testdata/integration_tests/BOX/BOXTEST2") , std::invalid_argument);
}

BOOST_AUTO_TEST_CASE( EQUAL ) {
    EclipseState state = makeState("testdata/integration_tests/BOX/BOXTEST1");
    std::shared_ptr<GridProperty<int> > pvtnum = state.getIntGridProperty("PVTNUM");
    std::shared_ptr<GridProperty<int> > eqlnum = state.getIntGridProperty("EQLNUM");
    size_t i,j,k;
    std::shared_ptr<const EclipseGrid> grid = state.getEclipseGrid();
    
    for (k = 0; k < grid->getNZ(); k++) {
        for (j = 0; j < grid->getNY(); j++) {
            for (i = 0; i < grid->getNX(); i++) {
                
                BOOST_CHECK_EQUAL( pvtnum->iget(i,j,k) , k );
                BOOST_CHECK_EQUAL( eqlnum->iget(i,j,k) , 77 + 2 * k );
                
            }
        }
    }
}



BOOST_AUTO_TEST_CASE( PERMX ) {
    EclipseState state = makeState("testdata/integration_tests/BOX/BOXTEST1");
    std::shared_ptr<GridProperty<double> > permx = state.getDoubleGridProperty("PERMX");
    std::shared_ptr<GridProperty<double> > permy = state.getDoubleGridProperty("PERMY");
    std::shared_ptr<GridProperty<double> > permz = state.getDoubleGridProperty("PERMZ");
    size_t i,j,k;
    std::shared_ptr<const EclipseGrid> grid = state.getEclipseGrid();
    
    for (k = 0; k < grid->getNZ(); k++) {
        for (j = 0; j < grid->getNY(); j++) {
            for (i = 0; i < grid->getNX(); i++) {
                
                BOOST_CHECK_CLOSE( permx->iget(i,j,k) * 0.25 , permz->iget(i,j,k) , 0.001);
                BOOST_CHECK_EQUAL( permx->iget(i,j,k) * 2 , permy->iget(i,j,k));
                    
            }
        }
    }
}
