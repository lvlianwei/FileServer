/*==============================================================*/
/* DBMS name:      MySQL 5.0                                    */
/* Created on:     2020/5/21 17:55:54                           */
/*==============================================================*/


drop table if exists tbl_dep;

drop table if exists tbl_user;

drop table if exists tbl_user_detail;

/*==============================================================*/
/* Table: tbl_dep                                               */
/*==============================================================*/
create table tbl_dep
(
   dep_id               int not null auto_increment,
   dep_name             varbinary(40),
   dep_address          varchar(50),
   primary key (dep_id)
);

/*==============================================================*/
/* Table: tbl_user                                              */
/*==============================================================*/
create table tbl_user
(
   user_id              int not null auto_increment,
   dep_id               int,
   user_name            varbinary(30),
   password             varchar(30),
   phone_no             varchar(11),
   primary key (user_id)
);

/*==============================================================*/
/* Table: tbl_user_detail                                       */
/*==============================================================*/
create table tbl_user_detail
(
   user_id              int,
   user_address         varchar(50),
   user_gender          int,
   user_birth           time
);

alter table tbl_user add constraint FK_Reference_2 foreign key (dep_id)
      references tbl_dep (dep_id) on delete restrict on update restrict;

alter table tbl_user_detail add constraint FK_Reference_1 foreign key (user_id)
      references tbl_user (user_id) on delete restrict on update restrict;

