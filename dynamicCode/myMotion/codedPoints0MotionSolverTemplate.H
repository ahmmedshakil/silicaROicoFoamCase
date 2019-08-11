/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | Copyright (C) 2018-2019 OpenCFD Ltd.
     \\/     M anipulation  |
-------------------------------------------------------------------------------
                            | Copyright (C) YEAR AUTHOR,AFFILIATION
-------------------------------------------------------------------------------
License
    This file is part of OpenFOAM.

    OpenFOAM is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with OpenFOAM.  If not, see <http://www.gnu.org/licenses/>.

Description
    Template for use with dynamic code generation of a
    points0MotionSolver.

SourceFiles
    codedPoints0MotionSolverTemplate.C

\*---------------------------------------------------------------------------*/

#ifndef codedPoints0MotionSolverTemplate_H
#define codedPoints0MotionSolverTemplate_H

#include "points0MotionSolver.H"

//{{{ begin codeInclude
#include "transformField.H"
    #include <cstdlib>
    int rand();
//}}} end codeInclude

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

/*---------------------------------------------------------------------------*\
                     A templated codedPoints0MotionSolver
\*---------------------------------------------------------------------------*/

class myMotionPoints0MotionSolver
:
    public points0MotionSolver
{
    // Private Member Functions

        //- Report a message with the SHA1sum
        inline static void printMessage(const char* message)
        {
            Info<< message << " sha1: " << SHA1sum << '\n';
        }

        //- No copy construct
        myMotionPoints0MotionSolver
        (
            const myMotionPoints0MotionSolver&
        ) = delete;

        //- No copy assignment
        void operator=(const myMotionPoints0MotionSolver&) = delete;


public:

    //- SHA1 representation of the code content
    static constexpr const char* const SHA1sum = "62067f7b10fa0125d94f9830a47fbec5f6ffbf8f";

    //- Runtime type information
    TypeName("myMotion");


    // Constructors

        //- Construct from mesh and dictionary
        myMotionPoints0MotionSolver
        (
            const polyMesh& mesh,
            const IOdictionary&
        );


    //- Destructor
    virtual ~myMotionPoints0MotionSolver();


    // Member Functions

        //- Provide current points for motion. Uses current motion field
        virtual tmp<pointField> curPoints() const;

        //- Solve for motion
        virtual void solve()
        {}
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //

