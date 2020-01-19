# include <ctime>
# include <unistd.h>

using namespace std;

typedef time_t			t_time;
typedef struct timespec	t_tspec;

# define DBG_TIME_NSEC_TO_UL(ts) (ts->tv_sec * 1000000000 + ts->tv_nsec)
# define DBG_TIME_MKSEC_TO_UL(ts) (ts->tv_sec * 1000000 + ts->tv_nsec / 1000)
# define DBG_TIME_MLSEC_TO_UL(ts) (ts->tv_sec * 1000 + ts->tv_nsec / 1000000)
# define DBG_TIME_SEC_TO_UL(ts) (ts->tv_sec)


class Speed {

public:
	void	init_point() {
		clock_gettime(CLOCK_REALTIME, &timer);
	}
	void	print_sec(char *text) {
		printf("%s %ld\ns", text, (long)dbg_timer_point());
	}
	void	print_msec(char *text) {
		printf("%s %lfs\n", text, (double)dbg_timer_point_ms() / 1000);
	}
	void	print_mksec(char *text) {
		printf("%s %lfs\n", text, (double)dbg_timer_point_mk() / 1000000);
	}
private:
	t_tspec	timer;

	int		dbg_timer_checkp(t_tspec *ctimer)
	{
		if (clock_gettime(CLOCK_REALTIME, ctimer) < 0)
			return (-1);
		if (dbg_timer_sub(ctimer, &timer) < 0)
			return (-1);
		return (0);
	}
	t_time	dbg_timer_point_ms(void)
	{
		t_tspec			chp_tsp;

		if (dbg_timer_checkp(&chp_tsp) < 0)
			return (-1);
		return (DBG_TIME_MLSEC_TO_UL((&chp_tsp)));
	}

	t_time	dbg_timer_point_mk(void)
	{
		t_tspec			chp_tsp;

		if (dbg_timer_checkp(&chp_tsp) < 0)
			return (-1);
		return (DBG_TIME_MKSEC_TO_UL((&chp_tsp)));
	}

	t_time	dbg_timer_point(void)
	{
		t_tspec			chp_tsp;

		if (dbg_timer_checkp(&chp_tsp) < 0)
			return (-1);
		return (DBG_TIME_SEC_TO_UL((&chp_tsp)));
	}

	int					dbg_timer_sub(t_tspec *dst, t_tspec *src)
	{
		t_tspec			res;

		res.tv_nsec = 0;
		res.tv_sec = 0;
		res.tv_sec = dst->tv_sec - src->tv_sec;
		if (dst->tv_nsec >= src->tv_nsec)
			res.tv_nsec = dst->tv_nsec - src->tv_nsec;
		else
		{
			--(res.tv_sec);
			res.tv_nsec = (dst->tv_nsec + 1000000000) - src->tv_nsec;
		}
		if (res.tv_sec > dst->tv_sec)
		{
			dst->tv_sec = 0;
			dst->tv_nsec = 0;
			return (-2);
		}
		dst->tv_nsec = res.tv_nsec;
		dst->tv_sec = res.tv_sec;
		return (0);
	}

};
