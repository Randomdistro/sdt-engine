PDS_VERSION_ID        = PDS3
RECORD_TYPE           = STREAM
OBJECT                = TEXT
  INTERCHANGE_FORMAT    = ASCII
  PUBLICATION_DATE      = 2005-07-01
  NOTE                  = "N/A"
END_OBJECT            = TEXT

END

           First Cassini Solar Conjunction Experiment Raw Data Archive
                          (CO-SS-RSS-1-SCE1-V1.0)

                              AAREADME.TXT
                              1 July 2005
                        Elias Barbinis and Gene Goltz
                          Jet Propulsion Laboratory


=============================================================================
INTRODUCTION
=============================================================================

     This DVD contains archival raw, and ancillary/supporting radio science
data for the First Cassini Solar Conjunction Experiment conducted during the
Quiet Cruise subphase of the Cassini mission. These data are contained in
eight Volumes (DVDs). The radio observations were carried out using the
Cassini Spacecraft and Earth-based receiving stations of the NASA Deep Space
Network DSN).

     The table below lists the eight volumes and (very briefly) their
respective contents.


VOLUME_ID      Start Date           End Date
---------  ------------------- -------------------
CORS_0021  2002-06-06 (02/157) 2002-06-09 (02/160)
CORS_0022  2002-06-10 (02/161) 2002-06-13 (02/164)
CORS_0023  2002-06-14 (02/165) 2002-06-17 (02/168)
CORS_0024  2002-06-18 (02/169) 2002-06-21 (02/172)
CORS_0025  2002-06-22 (02/173) 2002-06-25 (02/176)
CORS_0026  2002-06-26 (02/177) 2002-06-29 (02/180)
CORS_0027  2002-06-30 (02/181) 2002-07-03 (02/184)
CORS_0028  2002-07-04 (02/185) 2002-07-05 (02/186)

=============================================================================
VOLUME SET INFORMATION
=============================================================================

    Each of the eight volumes has the structure illustrated in the diagram
below.

     The primary data types for these volumes are the Radio Science Receiver
(RSR) files, the Orbit Data Files (ODFs), and the Archival Tracking Data
Files, (ATDFs or TDFs). The primary data are stored in subdirectories RSR,
ODF and TDF,in per-day directories SCE1_ddd (where 'ddd' specifies the day of
year based on the start time of the data).

     The primary data files are accompanied by secondary data files. These
include 0158-Monitor (158) files, MON-5-15 (515) files, C-Kernel (CKF) files,
Earth Orientation Parameters (EOP) files, Ionosphere Calibration (ION) files,
Path Delay (PD1 and PD2) files, Spacecraft/Planetary Ephemeris
(SPK) files, Telemetry (TLM) files, and Troposphere Calibration (TRO) files.
Secondary data that cover a time span of less than 24 hours are stored in
subdirectories of SCE1_ddd (i.e., 158, 515, PD1, PD2 and TLM).
Secondary data that cover a time span greater than 24 hours are provided in
subdirectories CKF, EOP, ION, SPK and TRO in the SCE1_ANCILLARY directory.
Occasionally, when secondary data are not available, some of the
subdirectories for secondary data may be missing.

     The CATALOG directory contains summary information on the Cassini
mission, the spacecraft, radio science instrumentation, the data set, and
listings of references and personnel. These files are structured to
facilitate machine handling but are also intended to be human readable.

     The diagram below shows the organization of each volume, starting from
the root of the DVD.

     |===================================================================|
     |                                                                   |
     |    Cassini Radio Science RDA Directory Structure for SCE1         |
     |                                                                   |
     |===================================================================|
     |                                                                   |
     |  root                                                             |
     |   |                                                               |
     |   |- AAREADME.TXT                                                 |
     |   |- ERRATA.TXT                                                   |
     |   |- VOLDESC.CAT                                                  |
     |   |                                                               |
     |   |- [CATALOG]                                                    |
     |   |    |- CATINFO.TXT                                             |
     |   |    |- MISSION.CAT                                             |
     |   |    |- INSTHOST.CAT                                            |
     |   |    |- INST.CAT                                                |
     |   |    |- REF.CAT                                                 |
     |   |    |- PERSON.CAT                                              |
     |   |    |- PROJREF.CAT                                             |
     |   |    `- DATASET.CAT                                             |
     |   |                                                               |
     |   |- [DOCUMENT]                                                   |
     |   |    |- DOCINFO.TXT                                             |
     |   |    |- CASRSSIS.TXT                                            |
     |   |    `- ...                                                     |
     |   |                                                               |
     |   |- [INDEX]                                                      |
     |   |    |- INDXINFO.TXT                                            |
     |   |    |- INDEX.LBL                                               |
     |   |    |- INDEX.TAB                                               |
     |   |    |- CUMINDEX.LBL                                            |
     |   |    `- CUMINDEX.TAB                                            |
     |   |                                                               |
     |   |- [CALIB]                                                      |
     |   |    |- LSK_YYMMDD.TLS                                          |
     |   |    |- TSC_YYMMDD.SCK                                          |
     |   |    `- BORESIGHT_YYMMDD.TXT                                    |
     |   |                                                               |
     |   |- [SCE1_ANCILLARY]                                             |
     |   |    |- [CKF]                                                   |
     |   |    |- [EOP]                                                   |
     |   |    |- [ION]                                                   |
     |   |    |- [SPK]                                                   |
     |   |    `- [TRO]                                                   |
     |   |                                                               |
     |   `- [SCE1_ddd]                                                   |
     |        |- [158]                                                   |
     |        |- [515]                                                   |
     |        |- [ODF]                                                   |
     |        |- [PD1]                                                   |
     |        |- [PD2]                                                   |
     |        |- [RSR]                                                   |
     |        |- [TDF]                                                   |
     |        `- [TLM]                                                   |
     |===================================================================|



=============================================================================
ERRATA
=============================================================================

     A cumulative list of errors and changes is maintained in the
ERRATA.TXT file.

=============================================================================
DISC FORMAT
=============================================================================

     The disc is organized according to the PDS standard for "one data set,
many volumes."  This file (AAREADME.TXT), a PDS volume object definition
(VOLDESC.CAT), and the listing of errors and changes (ERRATA.TXT) are
included at the root level.  The following directories of descriptive
material are also at the root level:

           CALIB    contains a Leapsecond kernel file, a Spacecraft Clock
                    Conversion file and a Boresight Calibration Report.

          CATALOG   contains descriptive files for cataloging the data
                    on this disc.

          DOCUMENT  contains a plain text Software Interface Specification
                    (SIS) for the data types that do not have a full PDS
                    label.

          INDEX     contains index information on each of the data files
                    included in this disc; it also includes a cumulative
                    index to all files in this volume set.



=============================================================================
FILE FORMAT
=============================================================================

     All data files on the disc are accompanied by detached or attached PDS
labels, which describe their contents.

     Detached labels have the same file name as the data file except that the
label name has the suffix ".LBL".

     Detailed documentation on file structure and contents formatting is
available for all file types either through complete PDS labels or through
Software Interface Specifications (SISs) in the DOCUMENT directory.

     Text files (*.TXT file names) and catalog files (*.CAT file names) are
stream files.



=============================================================================
SOFTWARE
=============================================================================

     No software has been included as part of this archival product.

=============================================================================
ACKNOWLEDGMENTS
=============================================================================

     These data were collected under the auspices of the Cassini Project. Arv
Kliore of JPL is the Radio Science Team Leader. Members of the Radio Science
Systems Group (RSSG) involved in data acquisition included Aseel Anabtawi,
Sami Asmar, Elias Barbinis, Don Fleischman, Doug Johnston, Gene Goltz, and
Kamal Oudrhiri. Also, the contributions of Andy Hang for this PDS archive
are acknowledged.

=============================================================================
DISCLAIMER
=============================================================================

     Although considerable care has gone into making this volume set, errors
are both possible and likely.  Users of the data are advised to exercise the
same caution as they would when dealing with any other unknown data set.

     Reports of errors or difficulties would be appreciated.  Please contact
one of the persons listed below.


=============================================================================
COGNIZANT PERSONNEL
=============================================================================

     The persons most directly responsible for construction and release of
this volume set are Elias Barbinis and Gene Goltz, members of the Radio
Science Systems Group (RSSG) at the Jet Propulsion Laboratory. Although many
people contributed to the volume set, any faults in the product are theirs
alone.


     Aseel Anabtawi
     Cassini Radio Science Operations Technical Lead
     Jet Propulsion Laboratory
     4800 Oak Grove Drive
     M/S: 230-215
     Pasadena, CA 91109-8099
     Tel: 818-393-1073
     FAX: 818-393-9282
     Aseel.Anabtawi@jpl.nasa.gov

     Sami Asmar
     Cassini Radio Science Task Lead
     Jet Propulsion Laboratory
     4800 Oak Grove Drive
     M/S: 230-215
     Pasadena, CA 91109-8099
     Tel: 818-354-6288
     FAX: 818-393-9282
     Sami.Asmar@jpl.nasa.gov

     Elias Barbinis
     Cassini Radio Science Science Support Engineer
     Jet Propulsion Laboratory
     4800 Oak Grove Drive
     M/S: 230-215
     Pasadena, CA 91109-8099
     Tel: 818-393-0661
     FAX: 818-393-9282
     Elias.Barbinis@jpl.nasa.gov

     Don Fleischman
     Cassini Radio Science Data System Engineer
     Jet Propulsion Laboratory
     4800 Oak Grove Drive
     M/S: 230-215
     Pasadena, CA 91109-8099
     Tel: 818-393-1072
     FAX: 818-393-9282
     Don.U.Fleischman@jpl.nasa.gov

     Gene Goltz
     Cassini Radio Science Operations Engineer
     Jet Propulsion Laboratory
     4800 Oak Grove Drive
     M/S: 230-215
     Pasadena, CA 91109-8099
     Tel: 818-393-1142
     FAX: 818-393-9282
     Gene.L.Goltz@jpl.nasa.gov

     Doug Johnston
     Cassini Radio Science Software Engineer
     Jet Propulsion Laboratory
     4800 Oak Grove Drive
     M/S: 230-215
     Pasadena, CA 91109-8099
     Tel: 818-393-0663
     FAX: 818-393-9282
     Douglas.V.Johnston@jpl.nasa.gov


     Arv Kliore
     Cassini Radio Science Team Lead
     Jet Propulsion Laboratory
     4800 Oak Grove Drive
     M/S: 161-260
     Pasadena, CA 91109-8099
     Tel: 818-354-6164
     FAX: 818-393-4643
     Arvydas.J.Kliore@jpl.nasa.gov

     Kamal Oudrhiri
     Cassini Radio Science Systems Engineer
     Jet Propulsion Laboratory
     4800 Oak Grove Drive
     M/S: 230-215
     Pasadena, CA 91109-8099
     Tel: 818-393-1143
     FAX: 818-393-9282
     Kamal.Oudrhiri@jpl.nasa.gov

     Richard A. Simpson
     PDS Radio Science Adviser
     Center for Radar Astronomy
     Packard Building - Room 332
     Stanford University
     Stanford, CA 94305-9515
     Tel: 650-723-3525
     FAX: 650-723-9251
     rsimpson@magellan.stanford.edu

=============================================================================
ACRONYMS AND ABBREVIATIONS
=============================================================================

     158    Monitor File (0158-Monitor - file and/or directory)
     515    Monitor File (Mon-5-15 - file and/or directory)
     ATDF   Archival Tracking Data File (same as TDF)
     AWVR   Advanced Water Vapor Radiometer
     CKF    C-Kernel File (file and/or directory)
     CORS   Cassini Orbiter Radio Science Data
     DLT    Digital Linear Tape
     DSMS   Deep Space Mission System
     DSN    Deep Space Network
     DVD    Digital Versatile Disk
     DVD-R  Digital Versatile Disk - Recordable Media
     EOP    Earth Orientation Parameters File (file and/or directory)
     GWE    Gravitational Wave Experiment
     ION    Ionosphere Calibration File (file and/or directory)
     JPL    Jet Propulsion Laboratory
     MON    Monitor File
     NASA   National Aeronautics and Space Administration
     NAIF   Navigation Ancillary Information Facility
     NSSDC  National Space Science Data Center
     ODF    Orbit Data File (file and/or directory)
     PCF    Plasma Correction File (file and/or directory)
     PD1    Path Delay Data File from AWVR1 (file and/or directory)
     PD2    Path Delay Data File from AWVR2 (file and/or directory)
     PDS    Planetary Data System
     RDA    Raw Data Archive
     RS     Radio Science
     RSSG   Radio Science Systems Group
     RSR    Radio Science Receiver Data File (file and/or directory)
     RSS    Radio Science Subsystem
     SCE    Solar Conjunction Experiment
     SIS    Software Interface Specification
     SPICE  Information System produced by the NAIF Team
     SPK    SP-Kernel File (file and/or directory)
     TLM    Telemetry File (file and/or directory)
     TNS    Tracking and Navigation Service Data File (file and/or directory)
     TDF    Archival Tracking Data File (file and/or directory)
     TRO    Troposphere Calibration File (file and/or directory)

