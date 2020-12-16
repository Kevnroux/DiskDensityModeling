Tons of stuff going on. The csv files like GalacticNorthLattitute7.5.csv or Error_galactic_northLatitude.csv are generated
by the diskfitting program itself.Run angle_changer.py to modify some angles that dont exist in the SDSS version.
 Then, CalculateError.py is run it generates the calc_error_galacticnorthlat12.5 csv files.
 Finally the makescatter and makescatterError.py are run to generate the graphs. 