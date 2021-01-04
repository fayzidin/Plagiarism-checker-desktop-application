CREATE TABLE `users` (
  `id` int PRIMARY KEY,
  `username` varchar(50) UNIQUE NOT NULL,
  `password` varchar(50),
  `full_name` varchar(200),
  `student_id` varchar(10) UNIQUE NOT NULL
);

CREATE TABLE `subjects` (
  `id` int PRIMARY KEY,
  `name` varchar(50)
);

CREATE TABLE `files` (
  `id` int PRIMARY KEY,
  `subject_id` int,
  `user_id` int,
  `path_to_file` varchar(200),
  `upload_date` datetime
);

CREATE TABLE `assignments` (
  `id` int PRIMARY KEY,
  `name` varchar(50),
  `subject_id` int,
  `theme` varchar(50),
  `create_date` datetime,
  `valid_from` datetime,
  `valid_until` datetime
);

CREATE TABLE `submition` (
  `id` int PRIMARY KEY,
  `assignment_id` INT,
  `file_id` int,
  `user_id` int,
  `upload_date` datetime,
  `is_valid` boolean,
  `plagiarism_percentage` int,
  `simillar_file_ids` varchar(200)
);

ALTER TABLE `files` ADD FOREIGN KEY (`subject_id`) REFERENCES `subjects` (`id`);

ALTER TABLE `files` ADD FOREIGN KEY (`user_id`) REFERENCES `users` (`id`);

ALTER TABLE `assignments` ADD FOREIGN KEY (`subject_id`) REFERENCES `subjects` (`id`);

ALTER TABLE `submition` ADD FOREIGN KEY (`user_id`) REFERENCES `users` (`id`);

ALTER TABLE `submition` ADD FOREIGN KEY (`file_id`) REFERENCES `files` (`id`);

ALTER TABLE `submition` ADD FOREIGN KEY (`assignment_id`) REFERENCES `assignments` (`id`);
