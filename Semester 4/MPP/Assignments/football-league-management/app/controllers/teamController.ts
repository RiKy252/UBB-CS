import { Team } from '@/models';
import { TeamType } from '@/app/types/team';
import { Op } from 'sequelize';

// Get all teams
export const getTeams = async () => {
  try {
    const teams = await Team.findAll();
    
    // Calculate wins statistics for metadata
    const winsArray = teams.map((t: TeamType) => t.wins);
    const maxWins = Math.max(...winsArray, 0);
    const minWins = Math.min(...winsArray, 0);
    const avgWins = winsArray.length > 0 
      ? winsArray.reduce((acc, val) => acc + val, 0) / winsArray.length 
      : 0;
      // Calculate points and enhance with metadata
    const enhancedTeams = teams.map((team: TeamType, index: number) => {
      const gamesPlayed = team.wins + team.draws + team.losses;
      const points = (team.wins * 3) + team.draws;
      
      return {
        ...team,
        position: index + 1,
        gamesPlayed,
        points,
        metadata: {
          isMostWins: team.wins === maxWins && maxWins > 0,
          isLeastWins: team.wins === minWins && teams.length > 1,
          isAvgWins: Math.abs(team.wins - avgWins) < 1
        }
      };
    });
    
    // Sort by points by default
    enhancedTeams.sort((a, b) => b.points - a.points);
    
    // Update positions after sorting
    enhancedTeams.forEach((team, index) => {
      team.position = index + 1;
    });
    
    return enhancedTeams;
  } catch (error) {
    console.error('Error getting teams:', error);
    throw error;
  }
};

// Get team by ID or name
export const getTeamById = async (identifier: number | string) => {
  try {
    let team;
    
    if (typeof identifier === 'number') {
      team = await Team.findByPk(identifier);
    } else {
      team = await Team.findOne({
        where: { name: identifier }
      });
    }
    
    if (!team) {
      throw new Error('Team not found');
    }
    
    const gamesPlayed = team.wins + team.draws + team.losses;
    const points = (team.wins * 3) + team.draws;
    
    return {
      ...team.toJSON(),
      gamesPlayed,
      points
    };
  } catch (error) {
    console.error('Error getting team by ID:', error);
    throw error;
  }
};

// Create a new team
export const createTeam = async (teamData: Omit<TeamType, 'id' | 'createdAt' | 'updatedAt'>) => {
  try {
    const newTeam = await Team.create(teamData as any);
    return newTeam;
  } catch (error) {
    console.error('Error creating team:', error);
    throw error;
  }
};

// Update a team
export const updateTeam = async (id: number, teamData: Partial<TeamType>) => {
  try {
    const team = await Team.findByPk(id);
    
    if (!team) {
      throw new Error('Team not found');
    }
    
    await team.update(teamData);
    return team;
  } catch (error) {
    console.error('Error updating team:', error);
    throw error;
  }
};

// Delete a team
export const deleteTeam = async (identifier: number | string) => {
  try {
    let deleteCount;
    
    if (typeof identifier === 'number') {
      deleteCount = await Team.destroy({
        where: { id: identifier }
      });
    } else {
      deleteCount = await Team.destroy({
        where: { name: identifier }
      });
    }
    
    if (deleteCount === 0) {
      throw new Error('Team not found');
    }
    
    return { success: true };
  } catch (error) {
    console.error('Error deleting team:', error);
    throw error;
  }
};

// Search and sort teams
export const searchTeams = async (query: string, sortBy: string = 'points', order: string = 'DESC') => {
  try {
    const where = query ? {
      name: {
        [Op.iLike]: `%${query}%`
      }
    } : {};
    
    let orderField = sortBy;
    
    // Map virtual fields to actual db fields for sorting
    if (sortBy === 'points') {
      orderField = 'wins'; // We'll handle points sorting in JS after fetching
    } else if (sortBy === 'gamesPlayed') {
      // For games played we need custom logic too
      orderField = 'wins';
    }
    
    const teams = await Team.findAll({
      where,
      order: [[orderField, order]]
    });
    
    // Calculate wins statistics for metadata
    const winsArray = teams.map((t: TeamType) => t.wins);
    const maxWins = Math.max(...winsArray, 0);
    const minWins = Math.min(...winsArray, 0);
    const avgWins = winsArray.length > 0 
      ? winsArray.reduce((acc, val) => acc + val, 0) / winsArray.length 
      : 0;
    
    // Calculate points and enhance with metadata
    let enhancedTeams = teams.map((team: any) => {
      const gamesPlayed = team.wins + team.draws + team.losses;
      const points = (team.wins * 3) + team.draws;
      
      return {
        ...team.toJSON(),
        gamesPlayed,
        points,
        metadata: {
          isMostWins: team.wins === maxWins && maxWins > 0,
          isLeastWins: team.wins === minWins && teams.length > 1,
          isAvgWins: Math.abs(team.wins - avgWins) < 1
        }
      };
    });
    
    // Handle special sorting cases that require calculated fields
    if (sortBy === 'points') {
      enhancedTeams.sort((a, b) => {
        return order.toUpperCase() === 'ASC' ? a.points - b.points : b.points - a.points;
      });
    } else if (sortBy === 'gamesPlayed') {
      enhancedTeams.sort((a, b) => {
        return order.toUpperCase() === 'ASC' ? a.gamesPlayed - b.gamesPlayed : b.gamesPlayed - a.gamesPlayed;
      });
    }
    
    // Update positions
    enhancedTeams.forEach((team, index) => {
      team.position = index + 1;
    });
    
    return enhancedTeams;
  } catch (error) {
    console.error('Error searching teams:', error);
    throw error;
  }
};