// app/api/teams/[name]/route.ts
import { NextRequest, NextResponse } from 'next/server';
import Team from '@/models/Team';
import { processTeamsForDisplay } from '@/app/utils/team-utils';

// GET a single team by name
export async function GET(
  request: NextRequest,
  { params }: { params: { name: string } }
) {
  try {
    const { name } = params;
    
    // Find team by name
    const team = await Team.findOne({ where: { name } });
    
    if (!team) {
      return NextResponse.json(
        { error: 'Team not found' },
        { status: 404 }
      );
    }
    
    // Convert to plain object
    const plainTeam = team.get({ plain: true });
    
    // Process team data to add calculated properties
    // We put it in an array for processTeamsForDisplay and take the first result
    const processedTeam = processTeamsForDisplay([plainTeam])[0];
    
    return NextResponse.json(processedTeam);
  } catch (error) {
    console.error('Error fetching team:', error);
    return NextResponse.json(
      { error: 'Failed to fetch team' },
      { status: 500 }
    );
  }
}

// PUT to update team by name
export async function PUT(
  request: NextRequest,
  { params }: { params: { name: string } }
) {
  try {
    const { name } = params;
    const updateData = await request.json();
    
    // Find team by name
    const team = await Team.findOne({ where: { name } });
    
    if (!team) {
      return NextResponse.json(
        { error: 'Team not found' },
        { status: 404 }
      );
    }
    
    // Update team
    await team.update(updateData);
    
    // Get updated team with calculated properties
    const updatedTeam = processTeamsForDisplay([team.get({ plain: true })])[0];
    
    return NextResponse.json(updatedTeam);
  } catch (error) {
    console.error('Error updating team:', error);
    return NextResponse.json(
      { error: 'Failed to update team' },
      { status: 400 }
    );
  }
}

// DELETE team by name
export async function DELETE(
  request: NextRequest,
  { params }: { params: { name: string } }
) {
  try {
    const { name } = params;
    
    // Find team by name
    const team = await Team.findOne({ where: { name } });
    
    if (!team) {
      return NextResponse.json(
        { error: 'Team not found' },
        { status: 404 }
      );
    }
    
    // Delete the team
    await team.destroy();
    
    return NextResponse.json(
      { message: 'Team deleted successfully' },
      { status: 200 }
    );
  } catch (error) {
    console.error('Error deleting team:', error);
    return NextResponse.json(
      { error: 'Failed to delete team' },
      { status: 400 }
    );
  }
}