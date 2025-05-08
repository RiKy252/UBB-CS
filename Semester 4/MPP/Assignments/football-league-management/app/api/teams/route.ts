// app/api/teams/route.ts
import { NextRequest, NextResponse } from 'next/server';
import Team from '@/models/Team';
import { filterAndSortTeams } from '@/app/utils/team-utils';

export async function GET(request: NextRequest) {
  try {
    // Get query parameters
    const searchParams = request.nextUrl.searchParams;
    const query = searchParams.get('query') || '';
    const sortBy = searchParams.get('sortBy') || 'points';
    const order = searchParams.get('order') as 'asc' | 'desc' || 'desc';

    // Fetch all teams from database
    const teams = await Team.findAll();
    
    // Convert to plain objects
    const plainTeams = teams.map(team => team.get({ plain: true }));
    
    // Process, filter and sort teams
    const processedTeams = filterAndSortTeams(plainTeams, query, sortBy as any, order);
    
    return NextResponse.json(processedTeams);
  } catch (error) {
    console.error('Error fetching teams:', error);
    return NextResponse.json(
      { error: 'Failed to fetch teams' },
      { status: 500 }
    );
  }
}

export async function POST(request: NextRequest) {
  try {
    const teamData = await request.json();
    
    // Create new team in database
    const newTeam = await Team.create(teamData);
    
    return NextResponse.json(newTeam, { status: 201 });
  } catch (error) {
    console.error('Error creating team:', error);
    return NextResponse.json(
      { error: 'Failed to create team' },
      { status: 500 }
    );
  }
}

// app/api/teams/[name]/route.ts - This should be in a separate file
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
    
    return NextResponse.json({ message: 'Team deleted successfully' });
  } catch (error) {
    console.error('Error deleting team:', error);
    return NextResponse.json(
      { error: 'Failed to delete team' },
      { status: 500 }
    );
  }
}

// app/api/teams/sort/route.ts - This should be in a separate file
export async function GET_sort(request: NextRequest) {
  try {
    // Get query parameters
    const searchParams = request.nextUrl.searchParams;
    const query = searchParams.get('query') || '';
    const sortBy = searchParams.get('sortBy') || 'points';
    const order = searchParams.get('order') as 'asc' | 'desc' || 'desc';

    // Fetch all teams from database
    const teams = await Team.findAll();
    
    // Convert to plain objects
    const plainTeams = teams.map(team => team.get({ plain: true }));
    
    // Process, filter and sort teams
    const processedTeams = filterAndSortTeams(plainTeams, query, sortBy as any, order);
    
    return NextResponse.json(processedTeams);
  } catch (error) {
    console.error('Error fetching teams:', error);
    return NextResponse.json(
      { error: 'Failed to fetch teams' },
      { status: 500 }
    );
  }
}