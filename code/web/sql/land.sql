DROP DATABASE IF EXISTS `land`;
CREATE DATABASE `land`;
USE `land`;

CREATE TABLE `problems`
(
 `problem_id` int primary key auto_increment,
 `title` varchar(200) NOT NULL,
 `description` text NOT NULL,
 `input` text,
 `output` text,
 `sample_input` text,
 `sample_output` text,
 `hint` text,
 `source` text,
 `contest_id` int NOT NULL default 0,
 `contest_seq` int NOT NULL default 0,
 `time_limit` int NOT NULL default 1000,
 `memory_limit` int NOT NULL default 65536,
 `spj` tinyint NOT NULL default 0,
 `accepted` int NOT NULL default 0,
 `submitted` int NOT NULL default 0,
 `enabled` tinyint NOT NULL default 1,
 `reserved` text
) ENGINE=MyISAM DEFAULT CHARSET=utf8 AUTO_INCREMENT=1001; 

INSERT INTO `problems` 
(`problem_id`, `title`, `description`, `input`, `output`, `sample_input`, `sample_output`) VALUES
(NULL, "A+B Problem", "Calculate a + b", "Two integer a, b (0<=a, b<=10)", "Output a + b", "1 2", "3");

CREATE TABLE `users`
(
 `user_id` int primary key auto_increment,
 `username` char(20) NOT NULL,
 `password` char(50) NOT NULL,
 `nickname` varchar(100),
 `email` varchar(100),
 `school` varchar(100),
 `reg_time` datetime,
 `last_ip` char(20) default NULL,
 `submit` int NOT NULL default 0,
 `solved` int NOT NULL default 0,
 `enabled` tinyint NOT NULL DEFAULT 1,
 `share_code` tinyint NOT NULL DEFAULT 1,
 `group_ids` varchar(200) DEFAULT "",
 `solved_list` text
) ENGINE=MyISAM DEFAULT CHARSET=utf8; 
ALTER TABLE  `users` ADD INDEX (  `username` );

INSERT INTO `users`
(`user_id`, `username`, `password`, `nickname`, `email`, `school`, `reg_time`, `group_ids`) VALUES
(NULL, "root", MD5("123456"), "root", "acm@whu.edu.cn", "whu", "2010-3-22 14:29:00", "1"),
(NULL, "anonymous", MD5(""), "anonymous", "acm@whu.edu.cn", "whu", "2010-3-22 14:29:00", "");

CREATE TABLE `groups`
(
 `group_id` int primary key auto_increment,
 `group_name` char(50) NOT NULL,
 `description` varchar(200),
 `view_src` tinyint NOT NULL DEFAULT 0,
 `private_contest` tinyint NOT NULL DEFAULT 0,
 `admin` tinyint NOT NULL DEFAULT 0,
 `reserved` text NOT NULL default ""
) ENGINE=MyISAM DEFAULT CHARSET=utf8; 

INSERT INTO `groups` VALUES
(1, "root", "privileged user group", 1, 1, 1, "");

CREATE TABLE `sources`
(
 `source_id` int auto_increment,
 `problem_id` int NOT NULL,
 `user_id` int NOT NULL,
 `username` char(20) NOT NULL,
 `contest_id` int NOT NULL DEFAULT 0,
 `source_code` text,
 `length` int NOT NULL DEFAULT 0,
 `submit_time` datetime,
 `submit_ip` char(20),
 `lang` tinyint NOT NULL,
 `share` tinyint NOT NULL,
 `judge_time` datetime,
 `memory_usage` int NOT NULL,
 `time_usage` int NOT NULL,
 `result` int NOT NULL DEFAULT 0,
 `extra_info` text,
 primary key(`source_id`, `problem_id`, `user_id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8; 

CREATE TABLE `admin_sources`
(
 `source_id` int auto_increment,
 `problem_id` int NOT NULL,
 `user_id` int NOT NULL,
 `username` char(20) NOT NULL,
 `contest_id` int NOT NULL DEFAULT 0,
 `source_code` text,
 `length` int NOT NULL DEFAULT 0,
 `submit_time` datetime,
 `submit_ip` char(20),
 `lang` tinyint NOT NULL,
 `share` tinyint NOT NULL,
 `judge_time` datetime,
 `memory_usage` int NOT NULL DEFAULT 0,
 `time_usage` int NOT NULL DEFAULT 0,
 `result` int NOT NULL DEFAULT 0,
 `extra_info` text,
 primary key(`source_id`, `problem_id`, `user_id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8; 

CREATE TABLE `contests`
(
 `contest_id` int primary key auto_increment,
 `title` varchar(200),
 `description` text,
 `private` tinyint NOT NULL DEFAULT 0,
 `start_time` datetime,
 `end_time` datetime,
 `enabled` tinyint NOT NULL DEFAULT 1
) ENGINE=MyISAM DEFAULT CHARSET=utf8; 

CREATE TABLE `user_at_contest`
(
 `user_id` int NOT NULL,
 `username` char(20) NOT NULL,
 `contest_id` int NOT NULL,
 `accepts` int NOT NULL DEFAULT 0,
 `penalty` int NOT NULL DEFAULT 0,
 `info_json` text NOT NULL, 
 primary key (`user_id`, `contest_id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8; 

CREATE TABLE `problem_at_contest`
(
 `problem_id` int NOT NULL,
 `contest_id` int NOT NULL,
 `contest_seq` int NOT NULL DEFAULT 0,
 `AC` int NOT NULL DEFAULT 0,
 `PE` int NOT NULL DEFAULT 0,
 `CE` int NOT NULL DEFAULT 0,
 `WA` int NOT NULL DEFAULT 0,
 `RE` int NOT NULL DEFAULT 0,
 `TLE` int NOT NULL DEFAULT 0,
 `MLE` int NOT NULL DEFAULT 0,
 `OLE` int NOT NULL DEFAULT 0,
 `total` int NOT NULL DEFAULT 0,
 primary key(`problem_id`, `contest_id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8; 

CREATE TABLE `mails`
(
 `mail_id` int primary key auto_increment,
 `from_user_id` int NOT NULL DEFAULT 0,
 `from_username` char(20) NOT NULL,
 `to_user_id` int NOT NULL DEFAULT 0,
 `to_username` char(20) NOT NULL DEFAULT 0,
 `send_time` datetime NOT NULL,
 `title` char(100),
 `content` text,
 `unread` tinyint NOT NULL DEFAULT 1,
 `reader_del` tinyint NOT NULL DEFAULT 0,
 `writer_del` tinyint NOT NULL DEFAULT 0
) ENGINE=MyISAM DEFAULT CHARSET=utf8; 
