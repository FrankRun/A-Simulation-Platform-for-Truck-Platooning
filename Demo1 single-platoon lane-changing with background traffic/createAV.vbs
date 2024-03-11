Dim linkNo, laneNo, linkCoordinate,vehType,desSpeed,interaction
vehType = 700
desSpeed = 80 
linkNo = 2
laneNo = 1
linkCoordinate = 0  
interaction = True
Vissim.Net.Vehicles.AddVehicleAtLinkPosition vehType, linkNo, laneNo, linkCoordinate, desSpeed, interaction