
module.exports = (sequelize, DataTypes) => {
    const Player = sequelize.define("Player", {
      name: {
        type: DataTypes.STRING,
        allowNull: false,
      },
      position: {
        type: DataTypes.STRING,
      },
      age: {
        type: DataTypes.INTEGER,
      },
      nationality: {
        type: DataTypes.STRING,
      },
      jerseyNumber: {
        type: DataTypes.INTEGER,
      },
    });
  
    Player.associate = (models) => {
      Player.belongsTo(models.Team, {
        foreignKey: "teamId",
        onDelete: "CASCADE",
      });
    };
  
    return Player;
};
  