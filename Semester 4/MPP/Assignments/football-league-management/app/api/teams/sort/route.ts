// app/api/teams/sort/route.ts
import { NextRequest, NextResponse } from 'next/server';
import { Op } from 'sequelize';
import Team from '@/models/Team';
import { filterAndSortTeams } from '@/app/utils/team-utils';

export async function GET(request: NextRequest) {
  try {
    // Get query parameters
    const searchParams = request.nextUrl.searchParams;
    const query = searchParams.get('query') || '';
    const sortBy = searchParams.get('sortBy') || 'points';
    const order = searchParams.get('order') as 'asc' | 'desc' || 'desc';

    // Set up where clause for database query
    const where: any = query 
      ? {
          [Op.or]: [
            { name: { [Op.iLike]: `%${query}%` } },
            { coachName: { [Op.iLike]: `%${query}%` } },
            { homeStadium: { [Op.iLike]: `%${query}%` } },
            { country: { [Op.iLike]: `%${query}%` } }
          ]
        } 
      : {};

    // Fetch teams from database
    const teams = await Team.findAll({ where });
    
    if (teams.length === 0) {
      return NextResponse.json(
        { error: 'No teams found matching the query.' },
        { status: 404 }
      );
    }
    
    // Convert to plain objects
    const plainTeams = teams.map(team => team.get({ plain: true }));
    
    // Process, filter and sort teams
    const processedTeams = filterAndSortTeams(plainTeams, query, sortBy as any, order);
    
    return NextResponse.json(processedTeams);
  } catch (error) {
    console.error('Error filtering and sorting teams:', error);
    return NextResponse.json(
      { error: 'Internal server error', details: String(error) },
      { status: 500 }
    );
  }
}