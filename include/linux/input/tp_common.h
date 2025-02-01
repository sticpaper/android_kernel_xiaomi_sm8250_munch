#include <linux/kobject.h>

extern struct kobject *touchpanel_kobj;
#ifdef CONFIG_TOUCHSCREEN_XIAOMI_GAMEMODE_NODE
extern struct kobject *touch_game_kobj;
#endif

struct tp_common_ops {
	ssize_t (*show)(struct kobject *kobj, struct kobj_attribute *attr,
			char *buf);
	ssize_t (*store)(struct kobject *kobj, struct kobj_attribute *attr,
			 const char *buf, size_t count);
};

int tp_common_set_double_tap_ops(struct tp_common_ops *ops);
int tp_common_set_fod_status_ops(struct tp_common_ops *ops);
