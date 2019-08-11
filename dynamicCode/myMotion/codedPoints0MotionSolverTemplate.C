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

\*---------------------------------------------------------------------------*/

#include "codedPoints0MotionSolverTemplate.H"
#include "fvCFD.H"
#include "unitConversion.H"
#include "addToRunTimeSelectionTable.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

defineTypeNameAndDebug(myMotionPoints0MotionSolver, 0);

addRemovableToRunTimeSelectionTable
(
    motionSolver,
    myMotionPoints0MotionSolver,
    dictionary
);


// * * * * * * * * * * * * * * * Global Functions  * * * * * * * * * * * * * //

// dynamicCode:
// SHA1 = 62067f7b10fa0125d94f9830a47fbec5f6ffbf8f
//
// unique function name that can be checked if the correct library version
// has been loaded
extern "C" void myMotion_62067f7b10fa0125d94f9830a47fbec5f6ffbf8f(bool load)
{
    if (load)
    {
        // Code that can be explicitly executed after loading
    }
    else
    {
        // Code that can be explicitly executed before unloading
    }
}


// * * * * * * * * * * * * * * * Local Functions * * * * * * * * * * * * * * //

//{{{ begin localCode
// Generate new set of points
    tmp<pointField> twistColumn
    (
        const scalar& maxRotAngle,
        const pointField& points
    )
    {
        tmp<pointField> tnewPoints(new pointField(points));
        pointField& newPoints = tnewPoints.ref();

        const boundBox bb(points, true);
        const scalar zMin = bb.min()[vector::Z];
        const scalar zSpan = bb.span()[vector::Z];

        const volScalarField& p = db().lookupObject<volVectorField>("p");

        forAll(points, pointI)
        {
            const scalar x = points[pointI].component(0);
            const scalar y = points[pointI].component(1);
            const scalar z = points[pointI].component(2);
            const scalar U = points[pointI].U();

            // Scale the angle by height
            const scalar silicaDeposit = 0.001*(rand()%10);
            const scalar zr = z + silicaDeposit;
            if (z > 0.3)
            {
            newPoints[pointI] = vector(x, y, zr);
            }
            else
            {
            newPoints[pointI] = vector(x, y, z);
            }
        }
        return tnewPoints;
    }
//}}} end localCode


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

myMotionPoints0MotionSolver::myMotionPoints0MotionSolver
(
    const polyMesh& mesh,
    const IOdictionary& dict
)
:
    points0MotionSolver(mesh, dict, "myMotion")
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

myMotionPoints0MotionSolver::~myMotionPoints0MotionSolver()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tmp<pointField> myMotionPoints0MotionSolver::curPoints() const
{
    if (false)
    {
        printMessage("curPoints myMotion");
    }

//{{{ begin code
    const Time& tm = mesh().time();
    const pointField& p0 = points0();

    // Max twist pi at t=10
    const scalar maxRotAngle =
        constant::mathematical::pi*Foam::sin(degToRad(90.0/10.0*tm.value()));

    return twistColumn(maxRotAngle, p0);
//}}} end code
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// ************************************************************************* //

