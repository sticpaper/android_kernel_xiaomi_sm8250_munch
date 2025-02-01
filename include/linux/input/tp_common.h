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
#ifdef CONFIG_TOUCHSCREEN_XIAOMI_GAMEMODE_NODE
int tp_common_set_gamemode_ops(struct tp_common_ops *ops);
int tp_common_set_up_threshold_ops(struct tp_common_ops *ops);
int tp_common_set_tolerance_ops(struct tp_common_ops *ops);
#ifdef CONFIG_TOUCHSCREEN_SUPPORT_NEW_GAME_MODE
int tp_common_set_aim_sensitivity_ops(struct tp_common_ops *ops);
int tp_common_set_tap_stability_ops(struct tp_common_ops *ops);
int tp_common_set_expert_mode_ops(struct tp_common_ops *ops);
#else
int tp_common_set_wgh_min_ops(struct tp_common_ops *ops);
int tp_common_set_wgh_max_ops(struct tp_common_ops *ops);
int tp_common_set_wgh_step_ops(struct tp_common_ops *ops);
#endif
int tp_common_set_edge_filter_ops(struct tp_common_ops *ops);
int tp_common_set_touch_status_ops(struct tp_common_ops *ops);
#endif
