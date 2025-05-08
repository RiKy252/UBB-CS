import { DataTypes, Model } from 'sequelize';
import sequelize from '../config/database';
import { TeamType } from '@/app/types/team';

class Team extends Model<TeamType> implements TeamType {
  public id!: number;
  public name!: string;
  public coachName!: string;
  public homeStadium!: string;
  public foundedYear!: number;
  public wins!: number;
  public draws!: number;
  public losses!: number;
  public goalsScored!: number;
  public goalsConceded!: number;
  public players!: string[];
  public country!: string;
  public readonly createdAt!: Date;
  public readonly updatedAt!: Date;
}

Team.init(
  {
    id: {
      type: DataTypes.INTEGER,
      primaryKey: true,
      autoIncrement: true
    },
    name: {
      type: DataTypes.STRING,
      allowNull: false,
      unique: true
    },
    coachName: {
      type: DataTypes.STRING,
      allowNull: false
    },
    homeStadium: {
      type: DataTypes.STRING,
      allowNull: false
    },
    foundedYear: {
      type: DataTypes.INTEGER,
      allowNull: false
    },
    wins: {
      type: DataTypes.INTEGER,
      defaultValue: 0
    },
    draws: {
      type: DataTypes.INTEGER,
      defaultValue: 0
    },
    losses: {
      type: DataTypes.INTEGER,
      defaultValue: 0
    },
    goalsScored: {
      type: DataTypes.INTEGER,
      defaultValue: 0
    },
    goalsConceded: {
      type: DataTypes.INTEGER,
      defaultValue: 0
    },
    players: {
      type: DataTypes.ARRAY(DataTypes.STRING),
      defaultValue: []
    },
    country: {
      type: DataTypes.STRING,
      allowNull: false
    }
  },
  {
    sequelize,
    modelName: 'Team',
    tableName: 'teams',
    timestamps: true
  }
);

export default Team;