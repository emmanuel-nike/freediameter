#########################################################################
#	diameap.sql							#
#			DiamEAP extension				#
#  		 Users Information Database schema           		#
#  									#
#  									#
#									#
# MySQL command to load the script:					#
#    mysql> mysql -u username -p password diameap_ui <	diameap.sql	#
#									#
#########################################################################

-- --------------------------------------------------------

--
-- Table structure for table `authe`
--

CREATE TABLE IF NOT EXISTS `lte_authe` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `grp` int(11) NOT NULL,
  `attribute` varchar(255) CHARACTER SET latin1 COLLATE latin1_general_ci NOT NULL,
  `value` char(255) NOT NULL,
  PRIMARY KEY (`id`)
);

-- --------------------------------------------------------

--
-- Table structure for table `authz`
--

CREATE TABLE IF NOT EXISTS `lte_authz` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `grp` int(11) NOT NULL,
  `attribute` varchar(255) CHARACTER SET latin1 COLLATE latin1_general_ci NOT NULL,
  `op` set('==','>','>=','<','<=','!=','~=','=+','+==','+>','+>=','+<','+<=','+!=','+~=','==+','>+','>=+','<+','<=+','!=+') NOT NULL DEFAULT '==',
  `value` char(255) NOT NULL,
  PRIMARY KEY (`id`)
);

-- --------------------------------------------------------

--
-- Table structure for table `grp`
--

CREATE TABLE IF NOT EXISTS `lte_grp` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `grp_name` char(255) NOT NULL,
  `active` set('Y','N') NOT NULL DEFAULT 'Y',
  PRIMARY KEY (`id`)
);

-- --------------------------------------------------------

--
-- Table structure for table `subscribers`
--

CREATE TABLE IF NOT EXISTS `lte_subscribers` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `username` varchar(255) CHARACTER SET latin1 COLLATE latin1_general_ci NOT NULL,
  `vendor` int(11) NOT NULL DEFAULT '0',
  `password` varchar(255) CHARACTER SET latin1 COLLATE latin1_general_ci NOT NULL,
  `active` enum('Y','N') CHARACTER SET latin1 COLLATE latin1_general_ci NOT NULL DEFAULT 'Y',
  PRIMARY KEY (`id`)
);

-- --------------------------------------------------------

--
-- Table structure for table `subscriber_grp`
--

CREATE TABLE IF NOT EXISTS `lte_subscriber_grp` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `lte_subscriber` int(11) NOT NULL,
  `grp` int(11) NOT NULL,
  PRIMARY KEY (`id`)
);
