#include <unistd.h>
#include <pwd.h>
#include <grp.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>

int praseDir(char *path)
{
	struct stat st;
	int ret = stat(path,&st);
	if(ret == -1){
		perror("stat");
		return -1;
	}
	
//判断文件属性
	char perms[11] = {0};
	switch(st.st_mode & S_IFMT)
	{
		case S_IFLNK:
			perms[0] = 'l';
			break;
		case S_IFDIR:
			perms[0] = 'd';
			break;
		case S_IFREG:
			perms[0] = '-';
			break;
		case S_IFBLK:
			perms[0] = 'b';
			break;
		case S_IFCHR:
			perms[0] = 'c';
			break;
		case S_IFSOCK:
			perms[0] = 's';
			break;
		case S_IFIFO:
			perms[0] = 'p';
			break;
		default:
			perms[0] = '?';
			break;
	}
//判断文件权限
//所有者
	perms[1] = (st.st_mode & S_IRUSR) ? 'r' : '-';
	perms[2] = (st.st_mode & S_IWUSR) ? 'w' : '-';
	perms[3] = (st.st_mode & S_IXUSR) ? 'x' : '-';
//所属组
	perms[4] = (st.st_mode & S_IRGRP) ? 'r' : '-';
	perms[5] = (st.st_mode & S_IWGRP) ? 'w' : '-';
	perms[6] = (st.st_mode & S_IXGRP) ? 'x' : '-';
//其他人
	perms[7] = (st.st_mode & S_IROTH) ? 'r' : '-';
	perms[8] = (st.st_mode & S_IWOTH) ? 'w' : '-';
	perms[9] = (st.st_mode & S_IXOTH) ? 'x' : '-';
//硬连接数
	int linkNum = st.st_nlink;
//文件所有者
	char * fileuser = getpwuid(st.st_uid)->pw_name;
//文件所属组
	char * filegroup = getgrgid(st.st_gid)->gr_name;
//文件大小
	int filesize = (int)st.st_size;
//修改时间
	char *time =ctime(&st.st_mtime);
	char mtime[512] ={0};
	strncpy(mtime,time,strlen(time)-1);
	
	printf("%s %d %s %s %d %s\n",perms,linkNum,fileuser,filegroup,filesize,mtime);
	return 0;	
}


int main(int argc,char *argv[])
{
	uid_t uid;
	struct passwd *pwd;
	struct group *grp;
	char ** groupmember;

	uid = getuid();
	pwd = getpwuid(uid);
	if(!pwd){
		printf("couldn't not find out about user %d\n",(int)uid);
		return -1;
	}
	printf ( "当前登陆的用户名为：%s  uid:%d\n" , pwd->pw_name,getuid());
	printf("名字：%s\n",pwd->pw_gecos);
	printf ("User uid is %d\n",(int) (pwd->pw_uid));

	grp = getgrgid(pwd->pw_gid);
	if(!grp){
		printf("could not find group %d\n",(int)pwd->pw_gid);
		return -1;
	}


	
	printf("default group name is :%s group id :%d\n",grp->gr_name,pwd->pw_gid);
	
	printf("group member:\n");
	groupmember = grp->gr_mem;
	while(*groupmember){
		printf("%s\n",*groupmember);
		groupmember++;
	}


	praseDir("/Users");
	return  0;
}	
