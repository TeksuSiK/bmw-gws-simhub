var game_gear = $prop('DataCorePlugin.GameRawData.TruckValues.CurrentValues.DashboardValues.GearDashboards');
var game_manual = Number($prop('GameRawData.TruckValues.ConstantsValues.MotorValues.ShifterTypeValue') === 3);

return `SH;${game_gear};${game_manual};\n`