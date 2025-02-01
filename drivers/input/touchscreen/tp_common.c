#include <linux/input/tp_common.h>

struct kobject *touchpanel_kobj;
#ifdef CONFIG_TOUCHSCREEN_XIAOMI_GAMEMODE_NODE
struct kobject *touch_game_kobj;
#endif

#define TS_ENABLE_FOPS(type)                                        \
int tp_common_set_##type##_ops(struct tp_common_ops *ops)           \
{                                                                   \
	static struct kobj_attribute kattr =                        \
		__ATTR(type, (S_IWUSR | S_IRUGO), NULL, NULL);      \
	kattr.show = ops->show;                                     \
	kattr.store = ops->store;                                   \
	return sysfs_create_file(touchpanel_kobj, &kattr.attr);     \
}

#ifdef CONFIG_TOUCHSCREEN_XIAOMI_GAMEMODE_NODE
#define TOUCHGAME_FOPS(type)                                        \
int tp_common_set_##type##_ops(struct tp_common_ops *ops)           \
{                                                                   \
	static struct kobj_attribute kattr =                        \
		__ATTR(type, (S_IWUSR | S_IRUGO), NULL, NULL);      \
	kattr.show = ops->show;                                     \
	kattr.store = ops->store;                                   \
	return sysfs_create_file(touch_game_kobj, &kattr.attr);     \
}
#endif

TS_ENABLE_FOPS(double_tap)
TS_ENABLE_FOPS(fod_status)
#ifdef CONFIG_TOUCHSCREEN_XIAOMI_GAMEMODE_NODE
TOUCHGAME_FOPS(gamemode)
TOUCHGAME_FOPS(up_threshold)
TOUCHGAME_FOPS(tolerance)
#ifdef CONFIG_TOUCHSCREEN_SUPPORT_NEW_GAME_MODE
TOUCHGAME_FOPS(aim_sensitivity)
TOUCHGAME_FOPS(tap_stability)
TOUCHGAME_FOPS(expert_mode)
#else
TOUCHGAME_FOPS(wgh_min)
TOUCHGAME_FOPS(wgh_max)
TOUCHGAME_FOPS(wgh_step)
#endif
TOUCHGAME_FOPS(edge_filter)
TOUCHGAME_FOPS(touch_status)
#endif

static int __init tp_common_init(void)
{
	touchpanel_kobj = kobject_create_and_add("touchpanel", NULL);
	if (!touchpanel_kobj)
		return -ENOMEM;
#ifdef CONFIG_TOUCHSCREEN_XIAOMI_GAMEMODE_NODE
	touch_game_kobj = kobject_create_and_add("touch_game", touchpanel_kobj);
	if (!touch_game_kobj)
		return -ENOMEM;
#endif

	return 0;
}
core_initcall(tp_common_init);
